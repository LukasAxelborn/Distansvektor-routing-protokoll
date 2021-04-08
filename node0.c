#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4]; // [destiantions node][via node]
} dt0;

void sendpackets()
{
  struct rtpkt packet;

  packet.sourceid = 0;

  for (int i = 1; i < 4; i++)
  {
    packet.mincost[i] = dt0.costs[i][i];
  }
  packet.destid = 1;
  tolayer2(packet);

  packet.destid = 2;
  tolayer2(packet);

  packet.destid = 3;
  tolayer2(packet);
}

/* students to write the following two routines, and maybe some others */

void rtinit0()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt0.costs[i][j] = 999;
    }
  }

  dt0.costs[0][0] = 0;
  dt0.costs[1][1] = 1;
  dt0.costs[2][2] = 3;
  dt0.costs[3][3] = 7;

  sendpackets();
}

void rtupdate0(struct rtpkt *rcvdpkt)
{
  // ska använda djikstra algoritm

  const int via = rcvdpkt->sourceid;

  for (int destination = 0; destination < 4; destination++)
  {
    if (dt0.costs[destination][via] > dt0.costs[via][via] + rcvdpkt->mincost[destination])
    {
      dt0.costs[destination][via] = dt0.costs[via][via] + rcvdpkt->mincost[destination];

      sendpackets();
    }
  }
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
