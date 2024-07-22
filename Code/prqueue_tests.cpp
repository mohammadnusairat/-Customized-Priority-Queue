#include "prqueue.h"

#include "gtest/gtest.h"

using namespace std;

template <typename T>

/* REMINDER: map is initialized to be used to compare specific values of the BST */

string map_as_string(const map<T, vector<int>>& m) {
    ostringstream ss;
    for (const auto &e : m) {
        int priority = e.first;
        vector<int> values = e.second;
        for (size_t j = 0; j < values.size(); j++) {
            ss << priority << " value: " << values[j] << endl;
        }
    }
    return ss.str();
}

TEST(prqueue, DefaultConstructor) {
    // intialize prqueue using default constructor
    prqueue<int> pq;
    EXPECT_EQ(pq.size(), 0) << "Sizes are different." << endl;
    EXPECT_EQ(pq.getRoot(), nullptr) << "Root is not nullptr." << endl;
}

TEST(prqueue, CopyConstructor) {
    // intiliaze map and vector to fill prqueue #1
    map<int, vector<int>> mp;
    vector<int> vals = {11, 22, 33};
    vector<int> priorities = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals.size(); i++) {
        pq1.enqueue(vals[i], priorities[i]);
        mp[priorities[i]].push_back(vals[i]);
    }

    // initialize prqueue #2 using copy constructor
    prqueue<int> pq2(pq1);


    EXPECT_EQ(pq1.size(), pq2.size()) << "Sizes are different." << endl;
    EXPECT_EQ(pq1.as_string(), pq2.as_string()) << "as_string() return values are different." << endl;
}

TEST(prqueue, AssignmentOperator) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // intiliaze map and vector to fill prq #2
    map<int, vector<int>> mp2;
    vector<int> vals2 = {44, 55, 66};
    vector<int> priorities2 = {4, 5, 6};

    // initialize prqueue #2 
    prqueue<int> pq2;
    for (long unsigned int i = 0; i < vals2.size(); i++) {
        pq2.enqueue(vals2[i], priorities2[i]);
        mp2[priorities2[i]].push_back(vals2[i]);
    }

    // call assignment operator function
    pq1.operator=(pq2);


    EXPECT_EQ(pq1.as_string(), pq2.as_string()) << "as_string() return values are different." << endl;
    EXPECT_EQ(pq1.size(), pq2.size()) << "Sizes are different." << endl;

}

TEST(prqueue, Clear) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // call the clear function
    pq1.clear();
    // create empty pq
    prqueue<int> pq2;


    EXPECT_EQ(pq1.size(), 0) << "Sizes are different." << endl;
    EXPECT_EQ(pq2.as_string(), pq1.as_string()) << "as_string() return values are different." << endl;
}

TEST(prqueue, Clear_Duplicates) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33, 220};
    vector<int> priorities1 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // call the clear function
    pq1.clear();
    // create empty pq
    prqueue<int> pq2;


    EXPECT_EQ(pq1.size(), 0) << "Sizes are different." << endl;
    EXPECT_EQ(pq2.as_string(), pq1.as_string()) << "as_string() return values are different." << endl;

    // NOT TESTING INTERNAL STRUCTURE> MUST USE GETROOT()> FIGURE OUT HOW!!!
}

TEST(prqueue, Destructor) {
    EXPECT_TRUE(true) << "Not testing the destructor." << endl;
}

TEST(prqueue, Destrcutor_Duplicates) {
    EXPECT_TRUE(true) << "Not testing the destructor with duplicates." << endl;

    // NOT TESTING INTERNAL STRUCTURE> MUST USE GETROOT()> FIGURE OUT HOW!!!
}

TEST(prqueue, Enqueue) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // initiliaze prqueue #2 using enqueue function
    prqueue<int> pq2;
    pq2.enqueue(11, 1); pq2.enqueue(22, 2); pq2.enqueue(33, 3); 


    EXPECT_EQ(pq1.size(), pq2.size()) << "Sizes are different." << endl;
    EXPECT_EQ(pq1.as_string(), pq2.as_string()) << "as_string() return values are different." << endl;
}

TEST(prqueue, Enqueue_Duplicates) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33, 220};
    vector<int> priorities1 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // initiliaze prqueue #2 using enqueue function
    prqueue<int> pq2;
    pq2.enqueue(11, 1); pq2.enqueue(22, 2); pq2.enqueue(33, 3); pq2.enqueue(220, 2);


    EXPECT_EQ(pq1.size(), pq2.size()) << "Sizes are different." << endl;
    EXPECT_EQ(pq1.as_string(), pq2.as_string()) << "as_string() return values are different." << endl;

    // NOT TESTING INTERNAL STRUCTURE> MUST USE GETROOT()> FIGURE OUT HOW!!!
}

TEST(prqueue, Peek) {
    /* test with int type */

    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // get the result and expected values
    int result = pq1.peek();
    int expected = mp1[1].at(0);

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;

    // clear the prqueue and test defualt value return
    pq1.clear();
    result = pq1.peek();
    expected = 0;

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;


    /* test with string type */

    // intiliaze map and vector to fill prq #1
    map<int, vector<string>> mp2;
    vector<string> vals2 = {"mohammad", "ashraf", "nusairat"};
    vector<int> priorities2 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<string> pq2;
    for (long unsigned int i = 0; i < vals2.size(); i++) {
        pq2.enqueue(vals2[i], priorities2[i]);
        mp2[priorities2[i]].push_back(vals2[i]);
    }

    // get the result and expected values
    string s_result = pq2.peek();
    string s_expected = mp2[1].at(0);

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;

    // clear the prqueue and test defualt value return
    pq2.clear();
    s_result = pq2.peek();
    s_expected = "";

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;
}

TEST(prqueue, Dequeue) {
    /* test with int type */

    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // get the result and expected values
    int result = pq1.dequeue();
    int expected = mp1[1].at(0);

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;

    // check if value was removed from the prqueue
    mp1.erase(1);
    result = pq1.size();
    expected = mp1.size();

    EXPECT_EQ(result, expected) << "Sizes are different." << endl;
    EXPECT_FALSE(pq1.peek() == 11) << "peek() returned the deleted value." << endl;

    // clear the prqueue and test defualt value return
    pq1.clear();
    result = pq1.dequeue();
    expected = 0;

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;


    /* test with string type */

    // intiliaze map and vector to fill prq #1
    map<int, vector<string>> mp2;
    vector<string> vals2 = {"mohammad", "ashraf", "nusairat"};
    vector<int> priorities2 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<string> pq2;
    for (long unsigned int i = 0; i < vals2.size(); i++) {
        pq2.enqueue(vals2[i], priorities2[i]);
        mp2[priorities2[i]].push_back(vals2[i]);
    }

    // get the result and expected values
    string s_result = pq2.dequeue();
    string s_expected = mp2[1].at(0);

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;

    // check if value was removed from the prqueue
    mp2.erase(1);
    result = pq2.size();
    expected = mp2.size();

    EXPECT_EQ(result, expected) << "Sizes are different." << endl;
    EXPECT_FALSE(pq2.peek() == "mohammad") << "peek() returned the deleted value." << endl;

    // clear the prqueue and test defualt value return
    pq2.clear();
    s_result = pq2.dequeue();
    s_expected = "";

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;
}

TEST(prqueue, Dequeue_Duplicates) {
    /* test with int type */

    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33, 220};
    vector<int> priorities1 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // get the result and expected values
    int result = pq1.dequeue();
    int expected = mp1[1].at(0);

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;

    // check if value was removed from the prqueue
    mp1.erase(1);
    result = pq1.size();
    expected = mp1.size() + 1;

    EXPECT_EQ(result, expected) << "Sizes are different." << endl;
    EXPECT_FALSE(pq1.peek() == 11) << "peek() returned the deleted value." << endl;

    // get the result and expected values for duplicate dequeue
    result = pq1.dequeue();
    expected = mp1[2].at(0);

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;

    // check if value was removed from the prqueue
    mp1.erase(2);
    result = pq1.size();
    expected = mp1.size() + 1;

    EXPECT_EQ(result, expected) << "Sizes are different." << endl;
    EXPECT_FALSE(pq1.peek() == 22) << "peek() returned the deleted value." << endl;

    // clear the prqueue and test defualt value return
    pq1.clear();
    result = pq1.dequeue();
    expected = 0;

    EXPECT_EQ(result, expected) << "Result: " << result << ". Expected: " << expected << "." << endl;


    /* test with string type */

    // intiliaze map and vector to fill prq #1
    map<int, vector<string>> mp2;
    vector<string> vals2 = {"mohammad", "ashraf", "nusairat", "mo"};
    vector<int> priorities2 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<string> pq2;
    for (long unsigned int i = 0; i < vals2.size(); i++) {
        pq2.enqueue(vals2[i], priorities2[i]);
        mp2[priorities2[i]].push_back(vals2[i]);
    }

    // get the result and expected values
    string s_result = pq2.dequeue();
    string s_expected = mp2[1].at(0);

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;

    // check if value was removed from the prqueue
    mp2.erase(1);
    result = pq2.size();
    expected = mp2.size() + 1;

    EXPECT_EQ(result, expected) << "Sizes are different." << endl;
    EXPECT_FALSE(pq2.peek() == "mohammad") << "peek() returned the deleted value." << endl;

    // get the result and expected values for duplicate dequeue
    s_result = pq2.dequeue();
    s_expected = mp2[2].at(0);

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;

    // check if value was removed from the prqueue
    mp2.erase(2);
    result = pq2.size();
    expected = mp2.size() + 1;

    EXPECT_EQ(result, expected) << "Sizes are different." << endl;
    EXPECT_FALSE(pq2.peek() == "mohammad") << "peek() returned the deleted value." << endl;

    // clear the prqueue and test defualt value return
    pq2.clear();
    s_result = pq2.dequeue();
    s_expected = "";

    EXPECT_EQ(s_result, s_expected) << "Result: " << s_result << ". Expected: " << s_expected << "." << endl;

    // NOT TESTING INTERNAL STRUCTURE> MUST USE GETROOT(). FIGURE OUT HOW!!!
}

TEST(prqueue, Size) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // call the size function
    pq1.size();


    EXPECT_EQ(pq1.size(), 3) << "Sizes are different." << endl;
}

TEST(prqueue, As_string) { // duplicates already being tested.
    map<int, vector<int>> mp;
    vector<int> vals = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    // Note that this uses duplicate priorities!
    vector<int> priorities = {1, 2, 3, 2, 2, 2, 2, 3, 3};
    prqueue<int> pq;
    for (long unsigned int i = 0; i < vals.size(); i++) {
        pq.enqueue(vals[i], priorities[i]);
        mp[priorities[i]].push_back(vals[i]);
    }
    EXPECT_EQ(pq.size(), vals.size());
    EXPECT_EQ(pq.as_string(), map_as_string(mp));
}

TEST(prqueue, Begin) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }
    
    // traverse to end of BST
    pq1.begin();
    int value;
    int priority;
    while (pq1.next(value, priority)) {}

    EXPECT_FALSE(pq1.next(value, priority));

    // test begin() function
    pq1.begin();
    EXPECT_TRUE(pq1.next(value, priority)) << "after calling begin(), next() failed.";
}

TEST(prqueue, Next) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33};
    vector<int> priorities1 = {1, 2, 3};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // initialize variables and prepare for next function usage
    pq1.begin();
    int value;
    int priority;
    int expectedVal;
    int expectedPrior;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters." << endl;

    expectedVal = 11; expectedPrior = 1;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters." << endl;

    expectedVal = 22; expectedPrior = 2;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters. value=" << value << ", priority=" << priority << endl;

    expectedVal = 33; expectedPrior = 3;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_FALSE(pq1.next(value, priority)) << "next function failed in returning false when attempting to set the parameters." << endl;

}

TEST(prqueue, BeginNext) {
    // initialize prqueue #1
    prqueue<int> pq1;
    int val; int prior;

    pq1.begin();
    EXPECT_FALSE(pq1.next(val, prior));

    pq1.enqueue(11, 1); pq1.enqueue(22, 2); pq1.enqueue(33, 3); pq1.enqueue(220, 2);

    pq1.begin(); pq1.next(val, prior);
    EXPECT_EQ(pq1.peek(), val);
}

TEST(prqueue, Begin_Duplicates) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33, 220};
    vector<int> priorities1 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }
    
    // traverse to end of BST
    pq1.begin();
    int value;
    int priority;
    while (pq1.next(value, priority)) {}

    EXPECT_FALSE(pq1.next(value, priority));

    // test begin() function
    pq1.begin();
    EXPECT_TRUE(pq1.next(value, priority)) << "after calling begin(), next() failed.";
}

TEST(prqueue, Next_Duplicates) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33, 220};
    vector<int> priorities1 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // visual test
    cout << "STARTING VISUAL TEST..." << endl;
    pq1.begin();
    int Visual_value;
    int Visual_priority;
    while (pq1.next(Visual_value, Visual_priority)) {
        cout << Visual_priority << " value: " << Visual_value << endl;
    }
    cout << "END OF VISUAL TEST." << endl;

    // initialize variables and prepare for next function usage
    pq1.begin();
    int value;
    int priority;
    int expectedVal;
    int expectedPrior;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters." << endl;

    expectedVal = 11; expectedPrior = 1;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters." << endl;

    expectedVal = 22; expectedPrior = 2;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters." << endl;

    expectedVal = 220; expectedPrior = 2;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_TRUE(pq1.next(value, priority)) << "next function failed in setting the parameters." << endl;

    expectedVal = 33; expectedPrior = 3;
    EXPECT_EQ(expectedVal, value) << "value returned is different." << endl;
    EXPECT_EQ(expectedPrior, priority) << "priority returned is different." << endl;

    // use the next function to get the next value and priority
    EXPECT_FALSE(pq1.next(value, priority)) << "next function failed in returning false when attempting to set the parameters." << endl;

}

TEST(prqueue, ComparisonOperator) {
    // intiliaze map and vector to fill prq #1
    map<int, vector<int>> mp1;
    vector<int> vals1 = {11, 22, 33, 220};
    vector<int> priorities1 = {1, 2, 3, 2};
    
    // initialize prqueue #1
    prqueue<int> pq1;
    for (long unsigned int i = 0; i < vals1.size(); i++) {
        pq1.enqueue(vals1[i], priorities1[i]);
        mp1[priorities1[i]].push_back(vals1[i]);
    }

    // intiliaze map and vector to fill prq #2
    map<int, vector<int>> mp2;
    vector<int> vals2 = {44, 55, 66, 4};
    vector<int> priorities2 = {4, 5, 6, 4};

    // initialize prqueue #2 
    prqueue<int> pq2;
    for (long unsigned int i = 0; i < vals2.size(); i++) {
        pq2.enqueue(vals2[i], priorities2[i]);
        mp2[priorities2[i]].push_back(vals2[i]);
    }

    EXPECT_FALSE(pq1.operator==(pq2)) << "pq1 and pq2 are the same. they should NOT be the same.";

    // intiliaze map and vector to fill prq #3
    map<int, vector<int>> mp3;
    vector<int> vals3 = {11, 22, 33, 220};
    vector<int> priorities3 = {1, 2, 3, 2};
    
    // initialize prqueue #3
    prqueue<int> pq3;
    for (long unsigned int i = 0; i < vals3.size(); i++) {
        pq3.enqueue(vals3[i], priorities3[i]);
        mp3[priorities3[i]].push_back(vals3[i]);
    }

    EXPECT_TRUE(pq1.operator==(pq3))<< "pq1 and pq3 are NOT the same. they SHOULD be the same.";

}

TEST(prqueue, visual_test_gradescope) {
    prqueue<int> pq;

    // Enqueue operations
    vector<pair<int, int>> operations = {
        {6, 0}, {1, 1}, {15, 2}, {2, 3}, {4, 4},
        {10, 5}, {20, 6}, {6, 7}, {1, 8}, {15, 9},
        {2, 10}, {4, 11}, {10, 12}, {20, 13}, {6, 14},
        {1, 15}, {15, 16}, {2, 17}, {4, 18}, {10, 19},
        {20, 20}
    };

    for (const auto& op : operations) {
        pq.enqueue(op.second, op.first);
    }

    // visual test
    cout << "STARTING VISUAL TEST..." << endl;
    pq.begin();
    int Visual_value;
    int Visual_priority;
    while (pq.next(Visual_value, Visual_priority)) {
        cout << Visual_priority << " value: " << Visual_value << endl;
    }
    cout << "END OF VISUAL TEST." << endl;

    EXPECT_TRUE(true);
}
