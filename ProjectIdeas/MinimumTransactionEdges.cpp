#include <bits/stdc++.h>
using namespace std;

int netTransferAmount(vector<vector<int>> graph, int personNumber) {
    int toGive = 0;
    int toReceive = 0;
    for (int i = 0; i < graph.size(); i++) {
        toGive += graph[personNumber][i];
        toReceive += graph[i][personNumber];
    }
    return toGive - toReceive;
}

int main() {
    int peoples;
    cin >> peoples;
    vector<vector<int>> graph(peoples, vector<int>(peoples, 0));

    for (int i = 0; i < peoples; i++) {
        int transactions;
        cin >> transactions;
        for (int j = 0; j < transactions; j++) {
            int toReceiveFrom;
            cin >> toReceiveFrom;
            int amountToReceive;
            cin >> amountToReceive;
            graph[toReceiveFrom][i] = amountToReceive;
        }
    }

    priority_queue<vector<int>, vector<vector<int>>> pq_positive;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq_negative;
    
    for (int i = 0; i < peoples; i++) {
        int val=netTransferAmount(graph, i);
        if(val>0)
        {
            pq_positive.push({val,i});
        }
        if(val<0)
        {
            pq_negative.push({val,i});
        }
    }

    vector<string> ans;
    while (!pq_positive.empty() && !pq_negative.empty()) {
        auto pos=pq_positive.top();
        auto neg=pq_negative.top();
        pq_positive.pop();
        pq_negative.pop();
        int maxm=pos[0];
        int minm=neg[0];
        
        if (maxm <= abs(minm)) {
            if(maxm+minm!=0)
             pq_negative.push({maxm+minm,neg[1]});
              ans.push_back(" From " + to_string(pos[1]) + " To " + to_string(neg[1]) + " Amount " + to_string(abs(maxm)));
        } else {
             if(maxm+minm!=0)
            pq_positive.push({maxm+minm,pos[1]});
             ans.push_back(" From " + to_string(pos[1]) + " To " + to_string(neg[1]) + " Amount " + to_string(abs(minm)));
          
        }
    }

    for (auto x : ans) {
        cout << x << endl;
    }

    return 0;
}
