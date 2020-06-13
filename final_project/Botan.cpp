#include "Botan.h"
#include "BruteForceIterator.h"

#include <iostream>
#include <memory>
#include <queue>
#include <thread>

#include <botan/argon2.h>
#include <botan/bcrypt.h>
#include <botan/hash.h>
#include <botan/hex.h>
#include <botan/pwdhash.h>
#include <botan/scrypt.h>

void sha256(const std::string &input, std::vector<uint8_t> &output) {
    std::unique_ptr<Botan::HashFunction> hash(Botan::HashFunction::create("SHA-256"));
    hash->update(input);
    output.clear();
    output.resize(hash->output_length());
    hash->final(output.data());
}

bool check_sha256(const std::string &password, const std::vector<uint8_t> &expected, std::vector<uint8_t> &buffer) {
    sha256(password, buffer);
    return expected == buffer;
}

void sha256_iterated(const std::string &input, std::vector<uint8_t> &output, int iterations) {
    std::unique_ptr<Botan::HashFunction> hash(Botan::HashFunction::create("SHA-256"));
    // First iteration
    hash->update(input);
    output.clear();
    output.resize(hash->output_length());
    hash->final(output.data());

    // Remaining iterations
    for (int i = 1; i < iterations; ++i) {
        hash->update(output);
        hash->final(output.data());
    }
}

bool check_sha256_iterated(const std::string &password, const std::vector<uint8_t> &expected, int iterations,
                           std::vector<uint8_t> &buffer) {
    sha256_iterated(password, buffer, iterations);
    return buffer == expected;
}

bool check_bcrypt(const std::string &input, const std::string &expected) {
    return Botan::check_bcrypt(input, expected);
}

bool check_argon2(const std::string &password, const std::string &expected) {
    return Botan::argon2_check_pwhash(password.c_str(), password.size(), expected);
}

void sha256_range(BruteForceIterator low, const BruteForceIterator &high) {

    auto expected = Botan::hex_decode("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");
    std::vector<uint8_t> buffer;
    while (low != high) {
        check_sha256(*low, expected, buffer);
        ++low;
    }
}

void iterated_sha256_range(BruteForceIterator low, const BruteForceIterator &high) {

    auto expected = Botan::hex_decode("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");
    std::vector<uint8_t> buffer;

    // 100 iterations per assignment requirements
    while (low != high) {
        check_sha256_iterated(*low, expected, 100, buffer);
        ++low;
    }
}

void bcrypt_range(BruteForceIterator low, const BruteForceIterator &high) {

    while (low != high) {
        check_bcrypt(*low, "$2y$12$5Xmto5aXd2I.3UhLab4gc.kXojwbikijoAdr4vsnqjs9H2C7VVndK");
        ++low;
    }
}

void argon2_range(BruteForceIterator low, const BruteForceIterator &high) {

    while (low != high) {
        check_argon2(*low, "$argon2d$v=19$m=8192,t=3,p=1$MTIzNDU2Nzg5YWJjZGVm$6C4pewOLgibFqWOo9mKTN2xV8KBRq7wjD8PM7DsoV0k");
        ++low;
    }
}

void sha256_queue(int block_limit, int block_size, int num_threads) {
    // Declare stuff
    std::vector<std::thread *> threads;
    SharedQueue<NameHere> tasks;

    // Start the threads
    threads.reserve(static_cast<size_t>(num_threads));
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(new std::thread(hash_cracker_sha256, std::ref(tasks)));
    }

    // Load the queue: the num_blocks is the value to check if we have reached our limit for tasks
    int num_blocks = 0;

    // Arbitrary alphabet and length for the hashes/second calculation
    BruteForce give_me_a_name("abcdefghijklmnopqrstuvwxyz", 6);
    auto begin = give_me_a_name.begin();

    while (begin != give_me_a_name.end()) {
        // Initializes end to equal begin
        auto end{begin};

        // Increments the iterator end by the value of block_size
        std::advance(end, block_size);

        // This pushes the task to the queue; do I need a min here? The min seemed specific to the perfect_worker case
        tasks.push(NameHere{begin, end});

        // Sets the begin iterator to the place of end to properly calculate the next block
        begin = end;

        // Increment num_blocks for conditional loop; this essentially controls the amount of tasks we will
        // push to the queue and consequently the total limit of hashes we will try to break
        ++num_blocks;

        // Break the loop when we have pushed enough tasks to the queue
        if (num_blocks > block_limit) {
            break;
        }
    }

    // Add quit tasks: this will push the sentinel values to the queue and tell the threads to quit
    for (int i = 0; i < num_threads; ++i) {
        tasks.push(NameHere{begin, begin}); // place sentinel value here.
    }

    // Join the threads
    for (auto i : threads) {
        i->join();
        delete i;
    }
}

void iterated_sha256_queue(int block_limit, int block_size, int num_threads) {
    // Declare stuff
    std::vector<std::thread *> threads;
    SharedQueue<NameHere> tasks;

    // Start the threads
    threads.reserve(static_cast<size_t>(num_threads));
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(new std::thread(hash_cracker_iterated_sha256, std::ref(tasks)));
    }

    // Load the queue: the num_blocks is the value to check if we have reached our limit for tasks
    int num_blocks = 0;

    // Arbitrary alphabet and length for the hashes/second calculation
    BruteForce give_me_a_name("abcdefghijklmnopqrstuvwxyz", 6);
    auto begin = give_me_a_name.begin();

    while (begin != give_me_a_name.end()) {
        // Initializes end to equal begin
        auto end{begin};

        // Increments the iterator end by the value of block_size
        std::advance(end, block_size);

        // This pushes the task to the queue; do I need a min here? The min seemed specific to the perfect_worker case
        tasks.push(NameHere{begin, end});

        // Sets the begin iterator to the place of end to properly calculate the next block
        begin = end;

        // Increment num_blocks for conditional loop; this essentially controls the amount of tasks we will
        // push to the queue and consequently the total limit of hashes we will try to break
        ++num_blocks;

        // Break the loop when we have pushed enough tasks to the queue
        if (num_blocks > block_limit) {
            break;
        }
    }

    // Add quit tasks: this will push the sentinel values to the queue and tell the threads to quit
    for (int i = 0; i < num_threads; ++i) {
        tasks.push(NameHere{begin, begin}); // place sentinel value here.
    }

    // Join the threads
    for (auto i : threads) {
        i->join();
        delete i;
    }
}

void bcrypt_queue(int block_limit, int block_size, int num_threads) {
    // Declare stuff
    std::vector<std::thread *> threads;
    SharedQueue<NameHere> tasks;

    // Start the threads
    threads.reserve(static_cast<size_t>(num_threads));
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(new std::thread(hash_cracker_bcrypt, std::ref(tasks)));
    }

    // Load the queue: the num_blocks is the value to check if we have reached our limit for tasks
    int num_blocks = 0;

    // Arbitrary alphabet and length for the hashes/second calculation
    BruteForce give_me_a_name("abcdefghijklmnopqrstuvwxyz", 6);
    auto begin = give_me_a_name.begin();

    while (begin != give_me_a_name.end()) {
        // Initializes end to equal begin
        auto end{begin};

        // Increments the iterator end by the value of block_size
        std::advance(end, block_size);

        // This pushes the task to the queue; do I need a min here? The min seemed specific to the perfect_worker case
        tasks.push(NameHere{begin, end});

        // Sets the begin iterator to the place of end to properly calculate the next block
        begin = end;

        // Increment num_blocks for conditional loop; this essentially controls the amount of tasks we will
        // push to the queue and consequently the total limit of hashes we will try to break
        ++num_blocks;

        // Break the loop when we have pushed enough tasks to the queue
        if (num_blocks > block_limit) {
            break;
        }
    }

    // Add quit tasks: this will push the sentinel values to the queue and tell the threads to quit
    for (int i = 0; i < num_threads; ++i) {
        tasks.push(NameHere{begin, begin}); // place sentinel value here.
    }

    // Join the threads
    for (auto i : threads) {
        i->join();
        delete i;
    }
}

void argon2_queue(int block_limit, int block_size, int num_threads) {
    // Declare stuff
    std::vector<std::thread *> threads;
    SharedQueue<NameHere> tasks;

    // Start the threads
    threads.reserve(static_cast<size_t>(num_threads));
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(new std::thread(hash_cracker_argon2, std::ref(tasks)));
    }

    // Load the queue: the num_blocks is the value to check if we have reached our limit for tasks
    int num_blocks = 0;

    // Arbitrary alphabet and length for the hashes/second calculation
    BruteForce give_me_a_name("abcdefghijklmnopqrstuvwxyz", 6);
    auto begin = give_me_a_name.begin();

    while (begin != give_me_a_name.end()) {
        // Initializes end to equal begin
        auto end{begin};

        // Increments the iterator end by the value of block_size
        std::advance(end, block_size);

        // This pushes the task to the queue; do I need a min here? The min seemed specific to the perfect_worker case
        tasks.push(NameHere{begin, end});

        // Sets the begin iterator to the place of end to properly calculate the next block
        begin = end;

        // Increment num_blocks for conditional loop; this essentially controls the amount of tasks we will
        // push to the queue and consequently the total limit of hashes we will try to break
        ++num_blocks;

        // Break the loop when we have pushed enough tasks to the queue
        if (num_blocks > block_limit) {
            break;
        }
    }

    // Add quit tasks: this will push the sentinel values to the queue and tell the threads to quit
    for (int i = 0; i < num_threads; ++i) {
        tasks.push(NameHere{begin, begin}); // place sentinel value here.
    }

    // Join the threads
    for (auto i : threads) {
        i->join();
        delete i;
    }
}

void hash_cracker_sha256(SharedQueue<NameHere> &tasks) {
    NameHere task{BruteForceIterator("a", 0), BruteForceIterator("a", 0)};
    for (;;) {
        switch (tasks.pop(task)) {
            case SharedQueue<NameHere>::PopResponse::no_task:
                std::this_thread::yield();
                break;
            case SharedQueue<NameHere>::PopResponse::terminate:
                return;
            case SharedQueue<NameHere>::PopResponse::task:
                if (task.low == task.high) {
                    // Quit task
                    return;
                }
                sha256_range(task.low, task.high);
                break;
        }
    }
}

void hash_cracker_iterated_sha256(SharedQueue<NameHere> &tasks) {
    NameHere task{BruteForceIterator("a", 0), BruteForceIterator("a", 0)};
    for (;;) {
        switch (tasks.pop(task)) {
            case SharedQueue<NameHere>::PopResponse::no_task:
                std::this_thread::yield();
                break;
            case SharedQueue<NameHere>::PopResponse::terminate:
                return;
            case SharedQueue<NameHere>::PopResponse::task:
                if (task.low == task.high) {
                    // Quit task
                    return;
                }
                iterated_sha256_range(task.low, task.high);
                break;
        }
    }
}

void hash_cracker_bcrypt(SharedQueue<NameHere> &tasks) {
    NameHere task{BruteForceIterator("a", 0), BruteForceIterator("a", 0)};
    for (;;) {
        switch (tasks.pop(task)) {
            case SharedQueue<NameHere>::PopResponse::no_task:
                std::this_thread::yield();
                break;
            case SharedQueue<NameHere>::PopResponse::terminate:
                return;
            case SharedQueue<NameHere>::PopResponse::task:
                if (task.low == task.high) {
                    // Quit task
                    return;
                }
                bcrypt_range(task.low, task.high);
                break;
        }
    }
}

void hash_cracker_argon2(SharedQueue<NameHere> &tasks) {
    NameHere task{BruteForceIterator("a", 0), BruteForceIterator("a", 0)};
    for (;;) {
        switch (tasks.pop(task)) {
            case SharedQueue<NameHere>::PopResponse::no_task:
                std::this_thread::yield();
                break;
            case SharedQueue<NameHere>::PopResponse::terminate:
                return;
            case SharedQueue<NameHere>::PopResponse::task:
                if (task.low == task.high) {
                    // Quit task
                    return;
                }
                argon2_range(task.low, task.high);
                break;
        }
    }
}

double time_sha256_queue(int block_limit, int block_size, int num_threads) {
    // Note std::endl here is used to ensure it prints prior to the computations starting
    //std::cout << "Start queue test, limit " << block_limit << " blocks with " << num_threads
    //<< " threads and block size " << block_size << std::endl;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    start = clock::now();

    sha256_queue(block_limit, block_size, num_threads);

    end = clock::now();

    //std::cout << "Finished. ";
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}

double time_iterated_sha256_queue(int block_limit, int block_size, int num_threads) {
    // Note std::endl here is used to ensure it prints prior to the computations starting
    //std::cout << "Start queue test, limit " << block_limit << " blocks with " << num_threads
    //<< " threads and block size " << block_size << std::endl;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    start = clock::now();

    iterated_sha256_queue(block_limit, block_size, num_threads);

    end = clock::now();

    //std::cout << "Finished. ";
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}

double time_bcrypt_queue(int block_limit, int block_size, int num_threads) {
    // Note std::endl here is used to ensure it prints prior to the computations starting
    //std::cout << "Start queue test, limit " << block_limit << " blocks with " << num_threads
    //<< " threads and block size " << block_size << std::endl;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    start = clock::now();

    bcrypt_queue(block_limit, block_size, num_threads);

    end = clock::now();

    //std::cout << "Finished. ";
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}

double time_argon2_queue(int block_limit, int block_size, int num_threads) {
    // Note std::endl here is used to ensure it prints prior to the computations starting
    //std::cout << "Start queue test, limit " << block_limit << " blocks with " << num_threads
    //<< " threads and block size " << block_size << std::endl;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    start = clock::now();

    argon2_queue(block_limit, block_size, num_threads);

    end = clock::now();

    //std::cout << "Finished. ";
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}