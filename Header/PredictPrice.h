#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

inline std::string predict2(std::string year_value)
{
    long year[1000] = { 0 }, life[1000] = { 0 };
    int counter{};
    std::string yr, avg;

    std::ifstream my_csv;
    my_csv.open("Dataset\\Price_Area.csv");

    if (my_csv.is_open())
    {
        while (!my_csv.eof())
        {
            getline(my_csv, yr, ',');
            year[counter] = stof(yr);

            getline(my_csv, avg, '\n');
            life[counter] = stof(avg);

            counter++;
        }
        my_csv.close();

    }
    else
        std::cout << "Error while opening file\n";

    double x_x[1000] = { 0 }, y_y[1000] = { 0 }, x_x_y_y[1000] = { 0 }, x_x2[1000] = { 0 };
    double sum1 = 0, sum2 = 0, avg1 = 0, avg2 = 0;
    double SUM1 = 0, SUM2 = 0;
    double AVG1 = 0, AVG2 = 0, Su1 = 0, Su2 = 0;
    double stand[1000] = { 0 }, Add[1000] = { 0 }, add = 0, assume = 0, var = 0, STDEV = 0;

    //Now we will calculate X, Y, m, b  for Y = b + mX

    for (int a = 0; a < counter; a++)      //Average for years
    {
        sum1 += year[a];
    }
    avg1 = sum1 / counter;

    for (int b = 0; b < counter; b++)   //Average for life expectancy
    {
        sum2 += life[b];
    }
    avg2 = sum2 / counter;

    //Performiing Standardlization
    for (int m = 0; m < counter; m++)     //standard deviation
    {
        assume = life[m] - avg2;
        Add[m] = assume * assume;
        add += Add[m];
    }
    var = add / (counter - 1);
    STDEV = std::sqrt(var);
    for (int n = 0; n < counter; n++)
    {
        stand[n] = (life[n] - avg2) / STDEV;
    }

    for (int c = 0; c < counter; c++)  //finding x-xbar
    {
        x_x[c] = year[c] - avg1;
    }

    double asd = 0, new_avg = 0;
    for (int gh = 0; gh < counter; gh++)   //Average for life expectancy
    {
        asd += stand[gh];
    }
    new_avg = asd / counter;

    for (int d = 0; d < counter; d++)  //finding y-ybar
    {
        y_y[d] = stand[d] - new_avg;
    }

    for (int i = 0; i < counter; i++)  //finding x-xbar average
    {
        Su1 += x_x[i];
    }
    AVG1 = Su1 / counter;

    for (int j = 0; j < counter; j++)  //finding y-ybar average
    {
        Su2 += y_y[j];
    }
    AVG2 = Su2 / counter;

    for (int e = 0; e < counter; e++)   //finding x-xbar * y-ybar
    {
        x_x_y_y[e] = x_x[e] * y_y[e];
    }

    for (int f = 0; f < counter; f++)  //finding x-xbar^2
    {
        x_x2[f] = x_x[f] * x_x[f];
    }

    for (int g = 0; g < counter; g++)  //finding sum of x-xbar * y-ybar full column
    {
        SUM1 += x_x_y_y[g];
    }

    for (int h = 0; h < counter; h++)  //finding sum of x-xbar^2 full column
    {
        SUM2 += x_x2[h];
    }

    double slope = 0, intercept = 0, x = 0;
    std::string answer;
    int Final = 0;
    double ans = 0;
    slope = double(SUM1 / SUM2);
    intercept = double(new_avg - (avg1 * slope));

    //Writng our trained model parameters 
    std::string str = " Trained-Params{\n";
    std::string str1 = "\n \"Weights\" :  ";
    std::string str2 = "\n \"Bias\" :        ";
    std::string weight, bias;
    weight = std::to_string(slope);
    bias = std::to_string(intercept);
    std::ofstream ModelW("Trained_Model\\Trained_Para_Price_Dataset.txt", std::ofstream::out);
    if (ModelW.is_open())
    {
        ModelW << str << str1 << weight + "\n" << str2 << bias + "\n\n }";
        ModelW.close();
    }
    else 
    std::cout << "Problem with opening file";

    //Calculations and Conversion

    int Number = 0;
    Number = std::stof(year_value);

    ans = intercept + (slope * Number);
    Final = ans * STDEV + avg2;
    Final /= 10000.0;

    answer = std::to_string(Final);

    return answer;
}
