
void maxi(int& max_len, int i, int j, int& low_id)
{
    if(max_len<j-i)
    {
        max_len=j-i;
        low_id=i;
    }
}

vector<int> Solution::maxone(vector<int> &b, int m) 
{
    int n = b.size();
    int max_len=INT_MIN, low_id=-1;
    int i=0,j=0; // [i,j)
    int leftm = m;
    bool shift_last=false;
    // always consider cases wrt the window paramert in2 pointer method
    while(i<n)
    {
        // if we can slide the window forawrd
        // cout<<i<<", "<<j<<endl;
        if (j==n||shift_last)
        {
            // what if i==j and leftm=0
            if(i==j)
            {
                // cout<<"increased\n";
                i++;
                j++;
                maxi(max_len,i,j,low_id);// not needed
                shift_last=false;
                continue;
            }
            // while i in window limits and there is not need pt change of states
            while(i<j&&b[i]==1)
            {
                i++;
                maxi(max_len,i,j,low_id); // still trying to chaneg the states tho not needed
            }

            // found the 1st zero 
            if(i<j&&b[i]==0)
            {
                i++;
                leftm++;
                maxi(max_len,i,j,low_id);// required
            }
            shift_last=false;
        }

        maxi(max_len,i,j,low_id);
        if(j<n)
        {
            if(b[j]==1)
            {
                // if slide without cost
                j++;
            }
            else
            {
                if(leftm>0)
                {
                    leftm--;
                    j++;
                }
                else
                {
                    // need to move back of the window to allow for a move ahead later
                    // cout<<"changed\n";
                    shift_last=true;
                }
            }
            maxi(max_len,i,j,low_id);
            continue;
        }
    }
    
    vector<int> ans;
    for(int i=low_id;i<low_id+max_len;i++)
    {
        ans.push_back(i);
    }
    return ans;
}

vector<int> Solution::maxone(vector<int> &arr, int m) {
    int n=arr.size();
    // Left and right indexes of current window
    int wL = 0, wR = 0; 
 
    // Left index and size of the widest window 
    int bestL = 0, bestWindow = 0; 
 
    // Count of zeroes in current window
    int zeroCount = 0; 
 
    // While right boundary of current window doesn't cross 
    // right end
    while (wR < n)
    {
        // If zero count of current window is less than m,
        // widen the window toward right
        if (zeroCount <= m)
        {
            if (arr[wR] == 0)
              zeroCount++;
            wR++;
        }
 
        // If zero count of current window is more than m,
        // reduce the window from left
        if (zeroCount > m)
        {
            if (arr[wL] == 0)
              zeroCount--;
            wL++;
        }
 
        // Updqate widest window if this window size is more
        if (wR-wL > bestWindow)
        {
            bestWindow = wR-wL;
            bestL = wL;
        }
    }
    vector<int> best;
    // Print positions of zeroes in the widest window
    for (int i=0; i<bestWindow; i++)
    {
        best.push_back(bestL+i);
    }
    return best;
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
}