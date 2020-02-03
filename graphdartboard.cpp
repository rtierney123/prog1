#include <stdio.h>
#include <math.h>
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

void drawgraph(std::vector<int> x, std::vector<int> y, std::string title, std::string file ){
    printf("drawing graph");
  
    
    // Set the size of output image = 1200x780 pixels
    plt::figure_size(1200, 780);

    // Plot line from given x and y data. Color is selected automatically.
    plt::plot(x, y);

    // Plot a line whose name will show up as "log(x)" in the legend.
    // plt::named_plot("log(x)", x, z);

    // Set x-axis to interval [0,1000000]
    //plt::xlim(0, 16);

    // Add graph title
    plt::title(title);

    // Enable legend.
    plt::legend();

   

       // save figure
    std::string  filename = "./"+file;
    std::cout << "Saving result to " << filename << std::endl;;
    plt::save(filename);

     plt::show();
    
}

std::tuple<std::vector<int>, std::vector<int>> get_data(int i1, int i2, std::string filename){
  std::string line;
  std::ifstream myfile(filename);
  std::vector<int> x;
  std::vector<int> y;
  if (myfile)
  {
    while ( getline(myfile, line))
    {
      std::stringstream ss(line);
      std::vector<std::string> result;
      while( ss.good() )
	{
	  std::string substr;
	  getline( ss, substr, ',' );
	  result.push_back( substr );
	}
      int x_val = 0;
      int y_val = 0;
      std::istringstream(result[i1]) >> x_val;
      std::istringstream(result[i2]) >> y_val;
      x.push_back(x_val);
      y.push_back(y_val);
    }
    myfile.close();
  }

  return std::make_tuple(x, y);
  
}

void plotprocessors(){
  std::tuple<std::vector<int>, std::vector<int>> data = get_data(2, 4, "processor-output.txt");
  std::vector<int> x = std::get<0>(data);
  std::vector<int> y = std::get<1>(data);
  drawgraph(x, y, "Amount of time to complete compared to number of processors.", "processorgraph.png");
}

void plotdarts(){
  std::tuple<std::vector<int>, std::vector<int>> data = get_data(0, 4, "dart-output.txt");
  std::vector<int> x = std::get<0>(data);
  std::vector<int> y = std::get<1>(data);
  drawgraph(x, y, "Amount of time to complete compared to number of darts thrown per trial.", "dartgraph.png");
}

int main(int argc, char** argv) {
  //plotprocessors();
  plotdarts();
}
