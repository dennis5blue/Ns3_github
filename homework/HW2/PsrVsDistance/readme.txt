Parameters Settings:
./waf --run "scratch/mywifi-phy-test PsrVsDistance --NPackets=1 --ErrorRateModel=1"
Remaining parameters are set as default

PsrVsDistance_0
Channel: YansWifiChannel
Propagation delay model: ConstantSpeedPropagationDelayModel
Propagation loss model: LogDistancePropagationLossModel
Error rate model: YansErrorRateModel
txMode: OfdmRate6Mbps & OfdmRate54Mbps

PsrVsDistance_1
Channel: YansWifiChannel
Propagation delay model: ConstantSpeedPropagationDelayModel
Propagation loss model: Cost231PropagationLossModel
Error rate model: YansErrorRateModel
txMode: OfdmRate6Mbps & OfdmRate54Mbps

PsrVsDistance_2
Channel: YansWifiChannel
Propagation delay model: ConstantSpeedPropagationDelayModel
Propagation loss model: ItuR1411LosPropagationLossModel
Error rate model: YansErrorRateModel
txMode: OfdmRate6Mbps & OfdmRate54Mbps
posTx->SetPosition (Vector (0.0, 0.0, 0.5));  posRx->SetPosition (Vector (m_input.distance, 0.0, 0.5));

PsrVsDistance_3
Channel: YansWifiChannel
Propagation delay model: ConstantSpeedPropagationDelayModel
Propagation loss model: OkumuraHataPropagationLossModel
Error rate model: YansErrorRateModel
txMode: OfdmRate6Mbps & OfdmRate54Mbps
posTx->SetPosition (Vector (0.0, 0.0, 0.5));  posRx->SetPosition (Vector (m_input.distance, 0.0, 0.5));
