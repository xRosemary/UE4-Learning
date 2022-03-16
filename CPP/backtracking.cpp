class Solution_1 {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<std::string> cases(n, std::string(n, '.'));
        backtrace(ans, cases, 0, n);
        return ans;
    }

    void backtrace(vector<vector<string>> &ans, vector<string> &cases, int row, int n){
        if(row == n){
            ans.push_back(cases);
            return;
        }

        for(int j = 0; j < n; j++){
            if(isValid(row, j, cases, n)){
                cases[row][j] = 'Q';

                backtrace(ans, cases, row+1, n);

                cases[row][j] = '.';

            } 
        }
    }
    
    bool isValid(int row, int col, vector<string> v, int n){
        for(int i=0; i<row; i++){
            if(v[i][col] == 'Q')
                return false;
        }

        for(int i=row-1, j=col+1; i>=0 && j<n; i--, j++){
            if(v[i][j] == 'Q')
                return false;
        }

        for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--){
            if(v[i][j] == 'Q')
                return false;
        }
        return true;
    }
};

class Solution_2 {
    bool posValid[30], negValid[30], colValid[30];
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;

        vector<std::string> cases(n, std::string(n, '.'));
        backtrace(ans, cases, 0, n);
        return ans;
    }

    void backtrace(vector<vector<string>> &ans, vector<string> &cases, int row, int n){
        if(row == n){
            ans.push_back(cases);
            return;
        }

        for(int j = 0; j < n; j++){
            if(colValid[j]==0 && posValid[row+j]==0 && negValid[j-row+n]==0){
                cases[row][j] = 'Q';
                colValid[j]=1; posValid[row+j]=1; negValid[j-row+n]=1;
                backtrace(ans, cases, row+1, n);
                colValid[j]=0; posValid[row+j]=0; negValid[j-row+n]=0;
                cases[row][j] = '.';
            } 
        }
    }
};
