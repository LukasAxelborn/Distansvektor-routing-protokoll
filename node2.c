#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt2;

void sendpackets2()
{
  struct rtpkt packet = {2, 0, 999, 999, 999, 999};

  for (int des = 0; des < 4; des++)
  {
    for (int via = 0; via < 4; via++)
    {
      if (dt2.costs[des][via] < packet.mincost[des])
      {
        packet.mincost[des] = dt2.costs[des][via];
      }
    }
  }

  packet.destid = 0;
  tolayer2(packet);

  packet.destid = 1;
  tolayer2(packet);

  packet.destid = 3;
  tolayer2(packet);
}

/* students to write the following two routines, and maybe some others */

void rtinit2()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt2.costs[i][j] = 999;
    }
  }

  dt2.costs[0][0] = 3;
  dt2.costs[1][1] = 1;
  dt2.costs[2][2] = 0;
  dt2.costs[3][3] = 2;

  sendpackets2();
}

void rtupdate2(struct rtpkt *rcvdpkt)
{
  int via = rcvdpkt->sourceid;

  for (int des = 0; des < 4; des++)
  {
    if (dt2.costs[des][via] > dt2.costs[via][via] + rcvdpkt->mincost[des])
    {
      dt2.costs[des][via] = dt2.costs[via][via] + rcvdpkt->mincost[des];

      sendpackets2();
    }
  }
}

void printdt2(struct distance_table *dtptr)

{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0],
         dtptr->costs[0][1], dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0],
         dtptr->costs[1][1], dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0],
         dtptr->costs[3][1], dtptr->costs[3][3]);
}
