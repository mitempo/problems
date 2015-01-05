#include <stdio.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <condition_variable>
#include <thread>

using namespace std;

/// <summary>
/// Connection point for send/receive operation.
/// Each sink is associated with a receiver. 
/// </summary>
template <typename T> struct Sink
{
    Sink() : isValuePresent(false) {}

    mutex enter; // Mutual exclusion for senders. A sender holds this lock during the entire send/receive session.

    T value;     // Value being sent.

    bool isValuePresent;    // True if the value is ready for consumption by receiver.
    mutex m;                // Protects the conditional variable below.
    condition_variable cv;  // Dual-purpose: used by the sender to signals "data is ready" and by the receiver to signal "data is received".
};

/// <summary>
/// Provides the execution environment and the API
/// for the agent's algorithm.
/// </summary>
template <typename T> class Engine
{
private:
    int _id;                 // Agent's unique identifier: [0; N)
    T _payload;              // Payload associated with the agent.
    int _n;                  // Total number of agents.
    Sink<T> *_psinks;        // Reference to the array of the agents' connection points.

public:
    template <typename U> Engine(int id, U&& payload, int n, Sink<T> psinks[]) : _id(id), _payload(forward<U>(payload)), _n(n), _psinks(psinks) {}

    int getN()         const { return _n; }
    int getMyId()      const { return _id; }
    int getMyPayload() const { return _payload; }

    template <typename U> void send(int id, U&& payload) const
    {
        Sink<T>& rv = _psinks[id];
        unique_lock<mutex> l(rv.enter);

        unique_lock<mutex> l2(rv.m);

        assert(!rv.isValuePresent);

        rv.value = forward<U>(payload);
        rv.isValuePresent = true;

        rv.cv.notify_one();
        rv.cv.wait(l2, [&]{ return !rv.isValuePresent; });
    }

    T receive() const
    {
        Sink<T>& rv = _psinks[_id];

        unique_lock<mutex> l2(rv.m);
        rv.cv.wait(l2, [&]{ return rv.isValuePresent; });

        rv.isValuePresent = false;
        rv.cv.notify_one();

        return rv.value;
    }
};

/// <summary>
/// The agent's algorithm that is a solution to the problem.
/// </summary>
void agent_algo(const Engine<int>& e)
{
    int id = e.getMyId();
    int payload = e.getMyPayload();
    int n = e.getN();

    vector<int> children;
    children.reserve(2);

    for (auto i : {id*2 + 1, id*2 + 2})
        if (i < n)
            children.push_back(i);

    for (size_t i = 0; i < children.size(); ++i)
        payload += e.receive();

    if (id != 0)
    {
        e.send((id - 1)/2, payload);
        payload = e.receive();
    }

    printf("%d: RESULT: %d\n", id, payload);

    for (auto i : children)
        e.send(i, payload);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("The number of agents must be specified\n");
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);

    // Create the connection points for the agents
    unique_ptr<Sink<int>[]> psinks(new Sink<int>[n]); // Sinks contain noncopyable/nonmovable std::mutex objects, so we can't use vector

    // Create the engines to run the agents
    vector<Engine<int>> engines;
    for (int i = 0; i < n; ++i)
        engines.push_back(Engine<int>(i, i, n, psinks.get()));

    // Start each agent in a separate thread
    vector<thread> threads;
    for (int i = 0; i < n; ++i)
        threads.push_back(thread([&engines, i](){ agent_algo(engines[i]); }));

    // Wait for all the agents to complete
    for (auto& t : threads)
        t.join();
}
