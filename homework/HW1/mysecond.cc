/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/flow-monitor-module.h"
#include <string.h>

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4
//    point-to-point  |    |    |    |
//                    ================
//                      LAN 10.1.2.0


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  uint32_t nCsma = 3;
  uint64_t timmyMaxPacket = 1;
  double timmyInterval = 1;
  uint64_t timmyPacketSize = 1024;
  //string timmyCsmaRate = "100Mbps"; 
    
  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.AddValue ("maxPacket", "timmy is god", timmyMaxPacket);
  cmd.AddValue ("interval", "mouda is god", timmyInterval);
  cmd.AddValue ("packetSize", "MJ is god", timmyPacketSize);

  cmd.Parse (argc,argv);

  //if (verbose)
    //{
    //  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    //  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    //}

  nCsma = nCsma == 0 ? 1 : nCsma;

  NodeContainer p2pNodes;
  p2pNodes.Create (2);

  NodeContainer csmaNodes;
  csmaNodes.Add (p2pNodes.Get (1));
  csmaNodes.Create (nCsma);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));//5
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms")); //2ms

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("15Mbps"));//100
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560))); //6560

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

  InternetStackHelper stack;
  stack.Install (p2pNodes.Get (0));
  stack.Install (csmaNodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csmaNodes);
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (30.0));

  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (timmyMaxPacket));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds(timmyInterval)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (timmyPacketSize));

  ApplicationContainer clientApps = echoClient.Install (csmaNodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (30.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  //pointToPoint.EnablePcapAll ("second");
  //csma.EnablePcap ("second", csmaDevices.Get (1), true);
  //csma.EnablePcap ("second", csmaDevices.Get (nCsma), true);

  //AsciiTraceHelper ascii;
  //pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("mysecond.tr"));

  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();
  
  Simulator::Stop (Seconds(30) );
  Simulator::Run ();
  
  monitor->SerializeToXmlFile("mysecond.xml", true, true);
  /*monitor-> CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  for (std::map<FlowId,FlowMonitor::FlowStats>::const_iterator iter = stats.begin(); iter != stats.end (); ++iter)
    {
      Ipv4FlowClassifier::FiveTuple t = classifier-> FindFlow (iter->first);
      NS_LOG_UNCOND("Flow ID:"<<iter->first<<"Src Addr"<<t.sourceAddress<<"Dest Addr"<<t.destinationAddress);
      NS_LOG_UNCOND("Tx packets = "<<iter->second.txPackets);
      NS_LOG_UNCOND("Rx packets = "<<iter->second.rxPackets);
      NS_LOG_UNCOND("Throughput:"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds() - iter->second.timeFirstTxPacket.GetSeconds())/1024<<"kbps");
      NS_LOG_UNCOND("Delay = "<<iter->second.delaySum/(1000*iter->second.rxPackets)<<" us");
    }
  */
  monitor->CheckForLostPackets ();
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  uint32_t txPacketSum = 0;
  uint32_t rxPacketSum = 0;
  uint32_t dropPacketSum = 0;
  uint32_t lostPacketSum = 0;
  double delaySum = 0;
  double throughputSum = 0;
  std::ofstream myfile("mysecond_3_1-1000_001_1024_speed6.txt",std::ios::app);
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
  {
    txPacketSum += i->second.txPackets;
    rxPacketSum += i->second.rxPackets;
    lostPacketSum += i->second.lostPackets;
    dropPacketSum += i->second.packetsDropped.size();
    throughputSum += (i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024);
    delaySum += i->second.delaySum.GetSeconds();
  }
  double delayAverage = 0;
  delayAverage = delaySum/rxPacketSum;
  std::cout << "  All Tx Packets: " << txPacketSum << "\n";
  std::cout << "  All Rx Packets: " << rxPacketSum << "\n";
  std::cout << "  All Delay: " << delayAverage <<"\n";
  std::cout << "  All Lost Packets: " << lostPacketSum << "\n";
  std::cout << "  All Drop Packets: " << dropPacketSum << "\n";
  std::cout << "  Packets Delivery Ratio: " << ((rxPacketSum *100)/txPacketSum) << "%" << "\n";
  std::cout << "  Packets Lost Ratio: " << ((lostPacketSum *100) /txPacketSum) << "%" << "\n";
  std::cout << "  Throughput: " << throughputSum << "\n";
  std::cout << "  Average Dealy: " << delayAverage << "\n";
  myfile<<throughputSum<<" "<<delayAverage<<"\n";
  Simulator::Destroy ();
  return 0;
}
