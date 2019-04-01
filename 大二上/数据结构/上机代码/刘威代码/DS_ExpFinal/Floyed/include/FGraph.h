#ifndef FGRAPH_H
#define FGRAPH_H


class FGraph
{
    public:
        FGraph();
        virtual ~FGraph();
        int VertexNum;
        int Array[1024][1024];
        int Path[1024][1024];
        void ShowArray();
        void ShowPath();
        void Floyed();
        int MaxMinDis;
    protected:

    private:
        int CharToNum(char c);
};

#endif // FGRAPH_H
