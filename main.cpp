#include "iostream"
#include "string"
#include "vector"
#include "algorithm"

enum Stroke
{
    Backstroke = 0,
    Breaststroke = 1,
    Butterfly = 2,
    Freestyle = 3
};

class Swimmer
{
    private:
        std::string gender;
        std::string name;
        int times[4];

    public:
        Swimmer(std::string gender_, std::string name_, int times_[4])
            : gender(gender_), name(name_)
        {

            for (int i = 0 ; i < 4 ; i++)
            {
                times[i] = times_[i];
            }
        }

        void printTimes()
        {
            for (int i = 0 ; i < 4 ; i++)
            {
                std::cout << times[i];
            }
        }

        int getTime(Stroke s)
        {
            return times[s];
        }

};

void permutationsHelper(int idx, std::vector<int> &nums, std::vector<std::vector<int>> &res) {
        if (idx == nums.size() - 1) {
            res.push_back(nums);
            return;
        }
            
        for (int i = idx ; i < nums.size() ; i++) {
            std::swap(nums[i], nums[idx]);
            permutationsHelper(idx+1, nums, res);
            std::swap(nums[i], nums[idx]);
        }     
    }
std::vector<std::vector<int>> getPermutations(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
            
    permutationsHelper(0, nums, res);
        
    return res;
}

void combinationsHelper(int n, int k, std::vector<std::vector<int>> &ans, std::vector<int> &combi){    
        if(combi.size() == k){
            ans.push_back(combi);
            return;
        }
            
        while(n > 0){
            combi.push_back(n);
            combinationsHelper(n-1, k, ans, combi);
            combi.pop_back();
            n--;
        }
    }

std::vector<std::vector<int>> getCombinations(int n, int k) {
    // from range 1 to n, all possible combinations of k numbers.
    // similar to nCr (math combinations concept) here n is n ans r is k.

    std::vector<std::vector<int>> ans;
    std::vector<int> combination;
        
    combinationsHelper(n, k, ans, combination);  
    return ans;
}

int calculateTimeOfPerm(std::vector<int> &perm, std::vector<std::vector<int>> &alltimes)
{
    int res = 0;
    for (int i = 0 ; i < perm.size() ; i++) 
    {
        res += alltimes[perm[i]-1][i];
    }
    return res;
}

void sortAllPerms(std::vector<std::vector<int>> &allperms, std::vector<std::vector<int>> &alltimes)
{
    std::vector<int> temp;
    for (int i = 0 ; i < allperms.size() ; i++)
    {
        for (int j = i ; j < allperms.size() ; j++)
        {
            if (calculateTimeOfPerm(allperms[i], alltimes) > calculateTimeOfPerm(allperms[j], alltimes))
            {
                temp = allperms[i];
                allperms[i] = allperms[j];
                allperms[j] = temp;
            }
        }
    }
}

void printAllCombs(std::vector< std::vector<std::vector<int>> > &allcombs)
{
    int cnt = 0;
    std::vector<std::vector<int>> comb;
    for (int h = 0 ; h < allcombs.size() ; h++)
    {
        comb = allcombs[h];
        std::cout << "Comb #" << h << "\n" ;
        for (int i = 0 ; i < comb.size() ; i++)
        {
            cnt++;
            std::cout << "Perm #" << h << " " ;
            for (int j = 0 ; j < comb[i].size() ; j++)
            {
                std::cout << comb[i][j] << " " ;// << (Stroke)j ; //
            }
            std::cout << "\n";

        }
        cnt = 0;
    }
}

void printAllPerms(std::vector< std::vector<int>> &allperms, std::vector< std::vector<int>> &alltimes)
{
    for (int i = 0 ; i < allperms.size() ; i++)
        {
            std::cout << "Perm #" << i << " " ;
            for (int j = 0 ; j < allperms[i].size() ; j++)
            {
                std::cout << allperms[i][j] << " " ;
            }
            std::cout << calculateTimeOfPerm(allperms[i], alltimes) << " \n";

        }
}

int main()
{
    std::cout << "Beginning\n";
    std::vector<int> times1{4, 5, 9, 3};
    std::vector<int> times2{3, 5, 5, 7};
    std::vector<int> times3{4, 7, 5, 5};
    std::vector<int> times4{7, 5, 8, 7};
    std::vector<int> times5{5, 5, 9, 8};
    std::vector<int> times6{4, 5, 6, 6};
    std::vector<std::vector<int>> alltimes;
    alltimes.push_back(times1);
    alltimes.push_back(times2);
    alltimes.push_back(times3);
    alltimes.push_back(times4);
    alltimes.push_back(times5);
    alltimes.push_back(times6);

    //Swimmer s("Male", "1", times);
    
    std::vector< std::vector<std::vector<int>> > allcombs;
    std::vector< std::vector<int>> allperms;
    std::vector<std::vector<int>> combs = getCombinations(6, 4);

    std::vector<int> x;
    std::vector<std::vector<int>> perms;
    for (int i = 0 ; i < combs.size() ; i++)
    {
        perms = getPermutations(combs[i]);
        allcombs.push_back(perms);
        //
        for (int j = 0 ; j < perms.size() ; j++) allperms.push_back(perms[j]);
    }

    //printAllPerms(allperms, alltimes);

    sortAllPerms(allperms, alltimes);
    printAllPerms(allperms, alltimes);
    //printAllCombs(allcombs);

    return 0;
}