#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include<bits/stdc++.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

using namespace std;
int N = 0;
int R = 0;
int M = 0;
int world_size;
int world_rank;
bool clear_output = false;
bool valid_entry = true;


//for leader (rank 0) only
float pi_sum = 0;


//convert polar to xy coordinates
std::tuple<float, float> getXYCoord(float L, float theta){
  float x = L * cos(theta);
  float y = L * sin(theta);
  return std::make_tuple(x, y);
}

//random number generator
float generateRandFloat(float size){
  float num = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return size * num;
}


//run a single instance of a dart throw
//return if landed in square or not
bool generateDartThrow(float radius){
  float square_size = radius / sqrt(2);
  float magnitude = generateRandFloat(pow(radius,2));
  float degree = generateRandFloat(2 * M_PI);
  std::tuple<float, float> coords = getXYCoord(sqrt(magnitude), degree);

  float x = std::get<0>(coords);
  float y = std::get<1>(coords);
  //printf("X  %f %d \n", x, world_rank);
  //printf("Y  %f %d \n", y, world_rank);

  return abs(x) <= square_size && abs(y) <= square_size;
}
//pass in the total number of darts run for test
//return number of darts landed in square for this processor
int dboard(int total_darts){
  int num_thrown = 0;
  int left_over_darts = total_darts % world_size;

  int radius = 10;
  
  if(world_rank == 0){
    num_thrown = total_darts/world_size + left_over_darts;
  }
  else{
    num_thrown = total_darts/world_size;
  }

   bool result = generateDartThrow(radius);
   //printf("%s %d \n", result  ? "hit square" : "miss square", world_rank);
  

  int hit_count = 0;
  for(int i = 0; i < num_thrown; i++){
    bool result = generateDartThrow(radius);
    
     if(result){
       hit_count++;
     }
  }
  return hit_count;
}


int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    int start_time = time(NULL);
    int total_start_time = 0;
    MPI_Reduce(&start_time, &total_start_time, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
     
    if(argc<3) {
      if(world_rank == 0){
	 printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
      }

       
    } else{
      if(argc > 3){
	clear_output = atoi(argv[3])>0 ? true : false ;
      }
      
      if(world_rank == 0){
	  N = atoi(argv[1]);
	  R = atoi(argv[2]);
      }

      MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Bcast(&R, 1, MPI_INT, 0, MPI_COMM_WORLD);

       if(world_rank == 0){
	 //drawgraph();
      }
    
      if(N < 5000000 || R > 100){
	valid_entry = false;
	if(world_rank == 0){
	  printf("Invalid arguement size.");
	}
      }

      if(valid_entry){
        srand(world_rank);
	int sums[R];
	int sum_count = 0;
	     for(int i = 0; i < R; i++){
	       M = dboard(N);
	    
	       //printf("Number of darts landed %d for rank %d \n", M, world_rank)
      
	       int sum = 0;
	       MPI_Reduce(&M, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
      
	       if(world_rank == 0){
		 float est_pi = static_cast<float>(N * 2)/static_cast<float>(sum);
		 pi_sum += est_pi;
		 sums[sum_count] = sum;
		 sum_count++;
	
	       }
	     
	     }
	     if(world_rank == 0){
		 float total_est_pi = pi_sum/R;
		 char output_buffer[50];
		 char raw_buffer[50];
		 int current_time = time(NULL);
		 int computation_time = current_time-total_start_time;
		 sprintf(output_buffer,  "N= %d, R= %d, P= %d, PI= %f\nTime= %d seconds\n", N, R, world_size, total_est_pi, computation_time);
		  sprintf(raw_buffer,  "%d, %d, %d, %f, %d\n", N, R, world_size, total_est_pi, computation_time);
		 
		 printf("%s\n",output_buffer);

		 ofstream myfile;
		 if(clear_output){
		    myfile.open("output.txt");
		 }
		 else{
		   myfile.open("output.txt", std::ios_base::app);
		 }
		 myfile << output_buffer;
		 myfile.close();

		 myfile.open("raw-output.txt", std::ios_base::app);
		 myfile << raw_buffer;
		 myfile.close();
	
		}

      }
    
    }
     
    // Finalize the MPI environment.
    MPI_Finalize();
}
