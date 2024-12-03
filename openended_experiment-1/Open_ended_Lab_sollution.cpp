#include <bits/stdc++.h>
using namespace std;

double cost_per_man;
double cost_per_equipment;

class Project
{
private:
    string name;
    float duration;
    float start_time;
    float end_time;
    float manpower;
    float funds;
    float profit;
    float cost;
    int equipment;

public:
    Project(string name, float duration, float start_time, float end_time, float manpower, float funds, int equipment)
    {
        this->name = name;
        this->duration = duration;
        this->start_time = start_time;
        this->end_time = end_time;
        this->manpower = manpower;
        this->funds = funds;
        this->profit = funds - (manpower * cost_per_man + equipment * cost_per_equipment);
        this->equipment = equipment;
        this->cost = (manpower * cost_per_man + equipment * cost_per_equipment);
    }

    string getName() const { return name; }
    float getDuration() const { return duration; }
    float getStartTime() const { return start_time; }
    float getEndTime() const { return end_time; }
    float getManpower() const { return manpower; }
    float getFunds() const { return funds; }
    float getProfit() const { return profit; }
    float getCost() const { return cost; }
    int getEquipment() const { return equipment; }
};

void displayProjects(const vector<Project> &projects)
{
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "|       Project Name       | Duration(days)  | Start Time(month) | End Time(month)  | Manpower(man)  | revinue+costs($)| Profit($)| cost |Equipments |\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------\n";

    if (projects.empty())
    {
        cout << "| NO projects added\n";
    }
    else
    {
        for (const Project &project : projects)
        {
            cout << "| " << left << setw(25) << project.getName()
                 << "| " << setw(16) << project.getDuration()
                 << "| " << setw(19) << project.getStartTime()
                 << "| " << setw(17) << project.getEndTime()
                 << "| " << setw(15) << project.getManpower()
                 << "| " << setw(13) << project.getFunds()
                 << "| " << setw(9) << project.getProfit()
                 << " |" << setw(7) << project.getCost()
                 << "| " << setw(11) << project.getEquipment() << "|\n";
        }
    }

    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void insertionSort(vector<Project> &projects)
{
    for (size_t i = 1; i < projects.size(); ++i)
    {
        Project key = projects[i];
        int j = i - 1;

        while (j >= 0 && projects[j].getEndTime() > key.getEndTime())
        {
            projects[j + 1] = projects[j];
            --j;
        }
        projects[j + 1] = key;
    }
}

void removeCollisions(vector<Project> &projects)
{
    for (size_t i = 0; i < projects.size(); ++i)
    {
        for (size_t j = i + 1; j < projects.size(); ++j)
        {
            if (projects[i].getEndTime() > projects[j].getStartTime())
            {
                if ((projects[i].getProfit() / projects[i].getDuration()) < (projects[j].getProfit() / projects[j].getDuration()))
                {
                    projects.erase(projects.begin() + i);
                }
                else
                {
                    projects.erase(projects.begin() + j);
                }
            }
        }
    }
}

float maximumProfit(const vector<Project> &projects, float totalFunds, vector<bool> &selectedProjects)
{
    int n = projects.size();
    vector<vector<float>> dp(n + 1, vector<float>(totalFunds + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= totalFunds; ++j)
        {
            if (projects[i - 1].getCost() <= j)
            {
                dp[i][j] = max(dp[i - 1][j], projects[i - 1].getProfit() + dp[i - 1][j - projects[i - 1].getCost()]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int maxProfit = dp[n][totalFunds];
    int remainingFunds = totalFunds;
    for (int i = n; i > 0 && maxProfit > 0; --i)
    {
        if (maxProfit != dp[i - 1][remainingFunds])
        {
            selectedProjects[i - 1] = true;
            maxProfit -= projects[i - 1].getProfit();
            remainingFunds -= projects[i - 1].getCost();
        }
    }

    return dp[n][totalFunds];
}

int main()
{
    cout << "---------------------------------------------\n";
    cout << "OPTIMAL RESOURSE ALLOCATION MANAGMENTS SYSTEM\n";
    cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";
    vector<Project> projects;
    float totalFunds;

    cout << "\nCompanies contrains:\n";
    cout << "***********************\n";
    cout << "Enter company's total funds: ";
    cin >> totalFunds;

    cout << "Enter per manpower cost: ";
    cin >> cost_per_man;

    cout << "Enter per equipment cost: ";
    cin >> cost_per_equipment;

    int choice;
    do
    {
        cout << "--------------------------------------\n";
        cout << " projects allcocation managment       \n";
        cout << "--------------------------------------\n";
        cout << "\n1. Add project\n";
        cout << "2. Sort projects based on end time\n";
        cout << "3. Remove colliding projects\n";
        cout << "4. Find maximum profit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice:\n>> ";
        cin >> choice;
        cout << "*****************************************\n";

        switch (choice)
        {
        case 1:
        {
            string name;
            float duration, start_time, end_time, manpower, funds;
            int equipment;

            cout << "Enter project name: ";
            cin >> name;
            cout << "Enter project duration (days): ";
            cin >> duration;
            cout << "Enter project start time (month): ";
            cin >> start_time;
            cout << "Enter project end time (month): ";
            cin >> end_time;
            cout << "Enter manpower: ";
            cin >> manpower;
            cout << "Enter project revenue with costs: ";
            cin >> funds;
            cout << "Enter equipments: ";
            cin >> equipment;

            projects.push_back(Project(name, duration, start_time, end_time, manpower, funds, equipment));
            break;
        }
        case 2:
            insertionSort(projects);
            cout << "Projects sorted based on end time.\n";
            break;
        case 3:
            removeCollisions(projects);
            cout << "Colliding projects removed.\n";
            break;
        case 4:
        {
            vector<bool> selectedProjects(projects.size(), false);
            float maxProfit = maximumProfit(projects, totalFunds, selectedProjects);
            cout << "Maximum profit achievable: $" << maxProfit << endl;
            cout << "Selected projects to achieve maximum profit:\n";
            for (size_t i = 0; i < selectedProjects.size(); ++i)
            {
                if (selectedProjects[i])
                {
                    cout << projects[i].getName() << endl;
                }
            }
            break;
        }
        case 5:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
        }

        if (choice != 5)
        {
            cout << "\nProjects:\n";
            displayProjects(projects);
        }
    } while (choice != 5);

    return 0;
}

