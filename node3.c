#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt3;

void sendpackets()
{
  struct rtpkt packet = {3, 0, 999, 999, 999, 999};

  for (int des = 0; des < 4; des++)
  {
    for (int via = 0; via < 4; via++)
    {
      if (dt3.costs[des][via] < packet.mincost[des])
      {
        packet.mincost[des] = dt3.costs[des][via];
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

void rtinit3()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt3.costs[i][j] = 999;
    }
  }

  dt3.costs[0][0] = 7;
  dt3.costs[2][2] = 2;
  dt3.costs[3][3] = 0;

  sendpackets();
}

void rtupdate3(struct rtpkt *rcvdpkt)
{
  int via = rcvdpkt->sourceid;

  for (int des = 0; des < 4; des++)
  {
    if (dt3.costs[des][via] > dt3.costs[via][via] + rcvdpkt->mincost[des])
    {
      dt3.costs[des][via] = dt3.costs[via][via] + rcvdpkt->mincost[des];

      sendpackets();
    }
  }
}

void printdt3(struct distance_table *dtptr)

{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}
