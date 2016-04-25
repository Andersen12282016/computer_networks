#include <iostream>
#include "HW3_Prog.h"
using namespace std;

/*  To send a distance vector from node 0 to node 1, example is provided as follows.
        Rtpkt test_rtpkt;
        creatertpkt(&test_rtpkt, 0, 1, distanceTablePtr->costs[0]);
        tolayer2(test_rtpkt);
*/

void rtinit(DistanceTable* ptr, int connectcosts[][4]) 
{
//TODO@@
/*  The DistanceTable that ptr points to is now to be initialized.
    This function should finish the followings:
    1.) Initialize distance table according to its node_id.
        Nodes that are not directly connected to itself, set the distance to 999.
        Except its own distance vector, fill all other distances to 999. (Since packets have not yet sent to update)

*/  for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            ptr->costs[i][j] = 999;
        }
    }
    int my_dv[4];
    int did = ptr->getNodeID();
    for(int k = 0; k<4; k++)
    {
        ptr->costs[did][k] = connectcosts[did][k];
        my_dv[k] = connectcosts[did][k];
    }


/*
    2.) Create and send routing pkt to your directly connected neighbors.
   Note that you should use connectcosts to initialize distanceTable.
   TA will change the connectcosts to verify your code. So DO NOT assign value without using connectcosts.
*/
    Rtpkt my_pkg[4];
    Rtpkt* my_ptr;
    for(int n = 0; n < 4; n++)
    {
        my_ptr = &(my_pkg[n]);
        if ((my_dv[n] < 999)&&(my_dv[n] >0))
        {
            creatertpkt(my_ptr, did, n, my_dv);
            tolayer2(my_pkg[n]);
        }
    }
    return;
}

void rtupdate(Rtpkt *rcvdpkt, DistanceTable* ptr, int connectcosts[][4])
{
//TODO@@
/*  A routing packet has received for the DistanceTable that ptr points to.
    Now you should update the DistanceTable.
    This function should finisih the followings:
    1.) Update distance table according to rcvdpkt.
        Check out the textbook to see how to update.
    2.) If the distance vector has been updated due to rcvdpkt, create and send routing pkt to your directly connected neighbors.
        Otherwise, do not need to send any routing packet.
*/
    int s = rcvdpkt->sourceid;
    int d = rcvdpkt->destid;
    
    for(int i = 0; i<4; i++)
    {
        ptr->costs[s][i] = rcvdpkt->mincost[i];
    }

    bool cost_change = false;
    for(int j = 0; j<4; j++)
    {
        if((j==s)||(j==d)) continue;
        if(ptr->costs[d][j]>(ptr->costs[d][s] + ptr->costs[s][j]))
        {
            ptr->costs[d][j] = (ptr->costs[d][s] + ptr->costs[s][j]);
            cost_change = true;
        }
    }
    if(cost_change == true)
    {
        int my_dv[4];
        for(int k = 0; k<4; k++)
        {
            my_dv[k] = ptr->costs[d][k];
        }

        Rtpkt my_pkg[4];
        Rtpkt* my_ptr;
        for(int n = 0; n < 4; n++)
        {
            my_ptr = &(my_pkg[n]);
            if ((connectcosts[d][n] < 999)&&(connectcosts[d][n] >0))
            {
                creatertpkt(my_ptr, d, n, my_dv);
                tolayer2(my_pkg[n]);
            }
        }      
    }
    return;
}
