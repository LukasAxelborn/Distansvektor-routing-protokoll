#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4]; // [scorce node][destiantions node]
} dt0;

/* students to write the following two routines, and maybe some others */

void rtinit0()
{
  dt0.costs[0][0] = 0;

  dt0.costs[0][1] = 1;
  dt0.costs[1][0] = 1;

  dt0.costs[0][2] = 3;
  dt0.costs[2][0] = 3;

  dt0.costs[0][3] = 7;
  dt0.costs[3][0] = 7;

  struct rtpkt packet;

  packet.sourceid = 0;

  for (int i = 1; i < 4; i++)
  {
    packet.mincost[i] = dt0.costs[0][i];
  }
  packet.destid = 1;
  tolayer2(packet);

  packet.destid = 2;
  tolayer2(packet);

  packet.destid = 3;
  tolayer2(packet);
}

void rtupdate0(struct rtpkt *rcvdpkt)
{
  // ska använda djikstra algoritm
}

void printdt0(struct distance_table *dtptr)
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1],
         dtptr->costs[1][2], dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1],
         dtptr->costs[2][2], dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1],
         dtptr->costs[3][2], dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost)

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
