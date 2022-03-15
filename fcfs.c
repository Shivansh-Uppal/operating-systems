#include <stdio.h>
int main(){
      int bt[1000]={0},at[1000]={0};
      float tat[1000]={0},wt[1000]={0};
      int n;

      printf("Enter the number of processes: ");
      scanf("%d",&n);

      for(int i=0;i<n;i++){
        printf("Enter the burst time %d: ",i+1);
        scanf("%d",&bt[i]);
        if(i>=1)
        bt[i]=bt[i-1]+bt[i];
      }

      for(int i=0;i<n;i++){
        printf("Enter the arrival time %d: ",i+1);
        scanf("%d",&at[i]);
      }

      for(int i=0;i<n;i++){
        tat[i]=bt[i]-at[i];
        tat[n]+=tat[i];
      }

      for(int i=0;i<n;i++){
        wt[i]=tat[i]-bt[i]+bt[i-1];
        wt[n]+=wt[i];
      }



      printf("Process no.\tBurst time\tArrival time\tTurn around time\t Waiting time\n");

      for(int i=0;i<n;i++){
        printf("%d\t\t %d\t\t %d\t\t%f\t\t%f\n",i+1,bt[i]-bt[i-1],at[i],tat[i],wt[i]);
      }

      printf("Average waiting time: %f\n",wt[n]/n);
      printf("Average turn around time: %f",tat[n]/n);

return 0;
}