#include "algo.hpp"
#include "merge.hpp"

void EDHM_Sample(WeightedHypergraph &hg, double hypergraphThreshold, PDD similarity, PII cnt, int seed)
{
    PII count = std::make_pair(0, 0);
    double orignalEntropy = hg.ComputeHypergraphEntropy();
    while ((hg.ComputeHypergraphEntropy() - orignalEntropy) / orignalEntropy < hypergraphThreshold)
    {
        std::vector<int> vv = vertexSample(hg, similarity.first, seed);
        if (vv.size() != 0)
        {
            hg.MergeVertex(vv);
            ++count.first;
        }

        std::vector<int> ee = hyperedgeSample(hg, similarity.second, seed);
        if (ee.size() != 0)
        {
            hg.MergeHyperedge(ee);
            ++count.second;
        }
        if (count.first >= cnt.first && count.second >= cnt.second)
            break;
    }
}