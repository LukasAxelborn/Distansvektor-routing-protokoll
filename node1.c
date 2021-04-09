#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt1;

void sendpackets()
{
  struct rtpkt packet = {1, 0, 999, 999, 999, 999};

  for (int des = 0; des < 4; des++)
  {
    for (int via = 0; via < 4; via++)
    {
      if (dt1.costs[des][via] < packet.mincost[des])
      {
        packet.mincost[des] = dt1.costs[des][via];
      }
    }
  }

  packet.destid = 1;
  tolayer2(packet);

  packet.destid = 2;
  tolayer2(packet);

  packet.destid = 3;
  tolayer2(packet);
}

/* students to write the following two routines, and maybe some others */

void rtinit1()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt1.costs[i][j] = 999;
    }
  }

  dt1.costs[0][0] = 1;
  dt1.costs[1][1] = 0;
  dt1.costs[2][2] = 1;

  sendpackets();
}

void rtupdate1(struct rtpkt *rcvdpkt)

{
  int via = rcvdpkt->sourceid;

  for (int des = 0; des < 4; des++)
  {
    if (dt1.costs[des][via] > dt1.costs[via][via] + rcvdpkt->mincost[des])
    {
      dt1.costs[des][via] = dt1.costs[via][via] + rcvdpkt->mincost[des];

      sendpackets();
    }
  }
}

void printdt1(struct distance_table *dtptr)

{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][2]);
}

void linkhandler1(int linkid, int newcost)

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
