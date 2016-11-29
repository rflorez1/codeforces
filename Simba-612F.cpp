#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e8 + 10;

int length, initPos;
long long sum = 0;
long long tmpSum = INF;
vector<int> dp;
vector<pair<int, int>> seq;
vector<vector<pair<int, int>>> seqVector;
vector<vector<int>> xx;

int getDistance(int x, int y) {
    int d = (length + y -x)%length;
    if (d > length - d)
        d -= length;
    return d;
}

int getWidth(int x, int y) {
    int w = y - x;
    if (w < 0)
        w += length;
    return w;
}

int nextIndex(int index, int sz) {
    if (index < (sz - 1))
        index++;
    else
        return 0;
    return index;
}
int prevIndex(int index, int sz) {
    if (index == 0)
        return (sz-1);
    else
        index--;
    return index;
}

void process(int index, vector<int> vec, int initPos, long long tmpSumm) {
    int sz = (int)vec.size();
    for (int i = 0, j = sz-1, k = 0; k < sz; i = nextIndex(i,sz), j = nextIndex(j,sz), k++) {
        int lower = vec[i];
        int upper = vec[j];
        int width = getWidth(lower, upper);
        int d = abs(getDistance(initPos, lower));

        if ((index+1) < (int)xx.size() && (int)xx[index+1].size() > 1) { // el proximo vector tiene más de un elemento
            seq.push_back(make_pair(i,0));
            process(index+1, xx[index+1], upper, tmpSumm + width + d);
            seq.pop_back();
            d = abs(getDistance(initPos, upper));
            seq.push_back(make_pair(j,1));
            process(index+1, xx[index+1], lower, tmpSumm + width + d);
            seq.pop_back();
        } else if ((index+1) < (int)xx.size() && (int)xx[index+1].size() == 1){ // el proximo vector tiene un solo elemento
            int last = xx[index+1][0];
            int dLast = abs(getDistance(upper, last));
            int dLast1 = abs(getDistance(lower, last));
            int d1 = abs(getDistance(initPos, upper));
            if ((tmpSumm + width + min(d + dLast, d1 + dLast1)) < tmpSum) {
                tmpSum = tmpSumm + width + min(d + dLast, d1 + dLast1);
                if ((d+dLast) < (d1+dLast1))
                    seq.push_back(make_pair(i,0));
                else
                    seq.push_back(make_pair(j,1));
                seqVector.clear();
                seqVector.push_back(seq);
                seq.pop_back();
            }

        } else { // éstamos en el vector final
            int d1 = abs(getDistance(initPos, upper)); // indice inicial es upper y recorrerlo en contra del sentido del reloj
            if ((tmpSumm + width + min(d,d1)) < tmpSum) {
                tmpSum = tmpSumm + width + min(d,d1);
                if (d < d1)
                    seq.push_back(make_pair(i,0));
                else
                    seq.push_back(make_pair(j,1));
                seqVector.clear();
                seqVector.push_back(seq);
                seq.pop_back();
            }
        }
    }
}

int main() {
    vector<int> x;
    int value, i = 0;
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin>>length>>initPos;
    while (i < length){
        cin>>value;
        x.push_back(value);
        i++;
    }
    vector<int> y(x.size());
    size_t n(0);
    generate(begin(y), end(y), [&]{ return n++; });
    sort(begin(y), end(y), [&](int i1, int i2) { return x[i1] < x[i2]; } );

    initPos--;
    vector<int> tmp;
    for(i = 0; i < length; i++) {
        if ((i < (length - 1)) && (x[y[i+1]] == x[y[i]])) {
            while ((i < (length-1)) && (x[y[i+1]] == x[y[i]])) {
                tmp.push_back(y[i]);
                i++;
            }
            tmp.push_back(y[i]);
            sort(tmp.begin(), tmp.end());

            xx.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(y[i]);
            xx.push_back(tmp);
            tmp.clear();
        }
    }

    int step, nn;
    for (i = 0; i < (int)xx.size(); i++ ) {
        if ((int)xx[i].size() > 1) { // son vectores con más de un elemento
            long long tmpSumm = 0;
            // Process the vector
            process(i, xx[i], initPos, tmpSumm);
            tmpSum = INF; // reset tmpSum for the next time
            seq.clear();
            nn = seqVector[0].size();
            for (int j = 0; j < nn; j++) {
                int bIndex = seqVector[0][j].first;
                int clockwise = seqVector[0][j].second; // 0: clockwise, 1: counterclockwise
                int sz = (int)xx[i+j].size();
                if (clockwise == 0) {
                    for (int k = bIndex, kk = 0; kk < sz; k = nextIndex(k, sz), kk++) {
                        step = getDistance(initPos, xx[i+j][k]);
                        sum += abs(step);
                        dp.push_back(step);
                        initPos = xx[i+j][k];
                    }
                } else {
                    for (int k = bIndex, kk = 0; kk < sz; k = prevIndex(k, sz), kk++) {
                        step = getDistance(initPos, xx[i+j][k]);
                        sum += abs(step);
                        dp.push_back(step);
                        initPos = xx[i+j][k];
                    }
                }
            }
            i = i + nn -1;
        } else {
            // vector de un sólo elemento
            step = getDistance(initPos, xx[i][0]);
            sum += abs(step);
            dp.push_back(step);
            initPos = xx[i][0];
        }
    }

    cout<<sum<<endl;
    for (i = 0; i < length; i++) {
        if (dp[i] >= 0)
            cout<<"+";
        cout<<dp[i]<<endl;
    }
    return 0;
}
