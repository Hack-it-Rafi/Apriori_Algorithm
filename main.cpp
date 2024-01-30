#include <bits/stdc++.h>
using namespace std;

int main()
{
    int NumOfItem, NumOfTransactions, supportCount;

    ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening the input file." << endl;
        return 1;
    }

    inputFile >> NumOfItem >> NumOfTransactions >> supportCount;

    int transactions[NumOfTransactions + 2][NumOfItem + 2] = {0};

    for (int i = 1; i <= NumOfTransactions; i++)
    {
        int NumOfTransactionsInRow;
        inputFile >> NumOfTransactionsInRow;

        for (int j = 1; j <= NumOfTransactionsInRow; j++)
        {
            int itemNum;
            inputFile >> itemNum;
            transactions[i][itemNum] = 1;
        }
    }
    inputFile.close();
    // One Item
    int C1[NumOfItem + 2] = {0};

    int checkSupport = 0;
    for (int i = 1; i <= NumOfItem; i++)
    {
        for (int j = 1; j <= NumOfTransactions; j++)
        {
            if (transactions[j][i] == 1)
            {
                C1[i]++;
            }
        }
    }

    int check = 1;

    int sumItem = 1;
    set<int> itemSet;
    pair<set<int>, int> pairOfSets;
    vector<pair<set<int>, int>> vectorOfPairs;

    for (int i = 1; i <= NumOfItem; i++)
    {
        itemSet.insert(i);
        for (int j = i + 1; j <= NumOfItem; j++)
        {
            int counter = 0;
            itemSet.insert(j);

            pairOfSets.first = itemSet;

            int checkSum = 0;
            for (int r = 1; r <= NumOfTransactions; r++)
            {
                for (const auto &element : itemSet)
                {
                    if (transactions[r][element] == 1)
                    {
                        checkSum = 1;
                    }
                    else
                    {
                        checkSum = 0;
                        break;
                    }
                }
                if (checkSum == 1)
                {
                    counter++;
                }
                checkSum = 0;
            }

            pairOfSets.second = counter;
            if (counter >= supportCount)
            {
                vectorOfPairs.push_back(pairOfSets);
            }
            counter = 0;

            if (!itemSet.empty())
            {
                auto lastElementIterator = prev(itemSet.end());
                itemSet.erase(lastElementIterator);
            }
        }
        itemSet.clear();
    }

    for (const auto &pair : vectorOfPairs)
    {
        cout << "Set: ";
        for (const auto &element : pair.first)
        {
            cout << element << " ";
        }
        cout << "| Int: " << pair.second << endl;
    }

    // More item

    int lengthOfVector = vectorOfPairs.size();
    int previousLengthOfVector = 0;
    int soldItems = 2;
    set<set<int>> uniqueSet;
    vector<set<int>> vectorOfSets;

    while (lengthOfVector > previousLengthOfVector)
    {
        vectorOfSets.clear();
        cout << soldItems << " items with support count "<<supportCount<<", total combination: " << lengthOfVector-previousLengthOfVector << endl
             << endl;
        set<int> set1;
        set<int> set2;

        for (int i = previousLengthOfVector; i < lengthOfVector; i++)
        {
            set1 = vectorOfPairs[i].first;
            int n = set1.size();
            for (int j = i + 1; j < lengthOfVector; j++)
            {
                set2 = vectorOfPairs[j].first;
                bool hasIntersection = any_of(set1.begin(), set1.end(),
                                              [&set2](int element)
                                              {
                                                  return set2.find(element) != set2.end();
                                              });
                if (hasIntersection)
                {
                    set_union(set1.begin(), set1.end(),
                              set2.begin(), set2.end(),
                              inserter(itemSet, itemSet.begin()));
                    int checkSum = 0;
                    int counter = 0;
                    int checkDom = 0;
                    auto it = find(vectorOfSets.begin(), vectorOfSets.end(), itemSet);

                    if (it == vectorOfSets.end())
                    {
                        vectorOfSets.push_back(itemSet);
                        // for (const auto &element : itemSet)
                        // {
                        //     cout << element << " ";
                        // }
                        // cout << endl;
                        pairOfSets.first = itemSet;
                        for (int r = 1; r <= NumOfTransactions; r++)
                        {
                            for (const auto &element : pairOfSets.first)
                            {
                                if (transactions[r][element] == 1)
                                {
                                    checkSum = 1;
                                }
                                else
                                {
                                    checkSum = 0;
                                    break;
                                }
                            }
                            if (checkSum == 1)
                            {
                                counter++;
                            }
                            checkSum = 0;
                        }
                        itemSet.clear();

                        pairOfSets.second = counter;
                        if (counter >= supportCount)
                        {
                            vectorOfPairs.push_back(pairOfSets);
                        }
                        counter = 0;

                        // cout << pairOfSets.second << endl;
                    }
                    itemSet.clear();
                }
            }
        }
        // cout << "hi" << endl;
        previousLengthOfVector = lengthOfVector;
        lengthOfVector = vectorOfPairs.size();
        // cout << vectorOfPairs.size() << endl;
        if (lengthOfVector > previousLengthOfVector)
        {
            soldItems++;
        }

        // for (const auto &pair : vectorOfPairs)
        for(int i=previousLengthOfVector; i<lengthOfVector; i++)
        {
            cout << "Set: ";
            for (const auto &element : vectorOfPairs[i].first)
            {
                cout << element << " ";
            }
            cout << "| Sold: " << vectorOfPairs[i].second << endl;
        }
    }
}