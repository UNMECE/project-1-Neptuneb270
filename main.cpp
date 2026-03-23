#include "main.h"
#include <iostream>

using namespace std;

enum cap_type {
   CONST_CURRENT,
   CONST_VOLTAGE
};

void init_cap(Capacitor *my_cap, int size, cap_type type);
void display(Capacitor *my_cap, int step);
void free_cap(Capacitor *my_cap);

int main() {
   //Setting values
   const double dt = 1e-10; 
   const double final_t = 5e-6; 
   const int resistance = 1e3;
   const int total_steps = (int)(final_t/dt); 
   const int n_steps = 200; //to display

   //Capacitor 1 (Const Current)
   Capacitor *my_cap1 = (Capacitor*) malloc(sizeof(Capacitor));
   init_cap(my_cap1, total_steps + 1, CONST_CURRENT);

   cout << "CONSTANT CURRENT CAPACITOR" << endl;
   for (int step = 1; step <= total_steps; step++) {
      //Update 
      my_cap1->time[step] =  step * dt;
      my_cap1->current[step] = my_cap1->current[step - 1];
      my_cap1->voltage[step] = my_cap1->voltage[step - 1] + 
         my_cap1->current[step - 1]*dt/my_cap1->C;
      //Display
      if (step % n_steps == 0) {
         display(my_cap1, step);
      }
   }
   
   //Capacitor 2 (Const Voltage)
   Capacitor *my_cap2 = (Capacitor*) malloc(sizeof(Capacitor));
   init_cap(my_cap2, total_steps + 1, CONST_VOLTAGE);
   
   cout << "CONSTANT VOLTAGE CAPACITOR" << endl;
   for (int step = 1; step <= total_steps; step++) {
      //Update 
      my_cap2->time[step] = step * dt;
      my_cap2->voltage[step] = my_cap2->voltage[step - 1];
      my_cap2->current[step] = my_cap2->current[step - 1] - 
         my_cap2->current[step - 1]*dt/resistance/my_cap2->C;
      //Display
      if (step % n_steps == 0) {
         display(my_cap2, step);
      }
   }

   //free
   free_cap(my_cap1);
   free_cap(my_cap2);

   return 0;
}

void init_cap(Capacitor *my_cap, int size, cap_type type) {
   const int resistance = 1e3; 

   my_cap->time = (double*) malloc(sizeof(double)*size);
   my_cap->voltage = (double*) malloc(sizeof(double)*size);
   my_cap->current = (double*) malloc(sizeof(double)*size);
   
   my_cap->time[0] = 0; 
   my_cap->voltage[0] = (type == CONST_CURRENT) ? 
      0.0 : 10.0;
   my_cap->C = 100e-12; 
   my_cap->current[0] = (type == CONST_VOLTAGE) ? 
      my_cap->voltage[0]/resistance : 1e-2;
}

void display(Capacitor *my_cap, int step) {
   cout << "Step " << step << " [" 
        << my_cap->time[step] << " seconds, "
        << my_cap->voltage[step] << " volts, "
        << my_cap->current[step] << " amps]" << endl;
}

void free_cap(Capacitor *my_cap) {
   free(my_cap->time);
   free(my_cap->voltage);
   free(my_cap->current);
   free(my_cap);
}
