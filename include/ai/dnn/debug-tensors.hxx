#pragma once

#include "debug-tensors.hh"
#include <fstream>

struct DebugTensorsHelper
{
    std::vector<Tensor> tensors;

    void add(const Vector& v)
    {
	tensors.push_back(Tensor(v));
    }

    void add(const Matrix& m)
    {
	tensors.push_back(Tensor(m));
    }

    void add(const Tensor& t)
    {
	tensors.push_back(t);
    }

    ~DebugTensorsHelper()
     {
	 if (tensors.empty())
	     return;
	 std::ofstream os("./cc_tensors.output");
	 TextSerialWriter sw(os);
	 sw << tensors.size();
	 for (const auto& t : tensors)
	     sw << t;
     }
};


inline DebugTensorsHelper& debug_get_helper()
{
    static DebugTensorsHelper helper;
    return helper;
}


inline void debug_add()
{}

template<class T, class... Tail>
void debug_add(T head, Tail... tail)
{
    debug_get_helper().add(head);   
    debug_add(tail...);
}


inline std::vector<Tensor> debug_load(const char* path)
{
    std::ifstream is(path);
    TextSerialReader sr(is);
    std::vector<Tensor> res;
    int len;
    sr >> len;
    for (int i = 0; i < len; ++i)
    {
	Tensor x;
	sr >> x;
	res.push_back(x);
    }

    return res;
}
