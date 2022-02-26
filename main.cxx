#include "tree.hxx"
#include <iostream>

int main(int argc, char** argv)
{
    try 
    {
        //std::vector<int> v = { 12, 11, 90, 82 , 7, 9};
        std::vector<int> v = { 26, 82, 16, 92, 33};
        //std::vector<int> v;

        Tree<int> t(v);

        DeepestNodes<int> deepestNodes = t.getDeepestNodes();
        deepestNodes.print();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}   