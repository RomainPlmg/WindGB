#ifndef __GB_H__
#define __GB_H__

#include <memory>

class CPU;
class RAM;

class GB {
   public:
    GB();
    ~GB();

    void Run();

   private:
    std::unique_ptr<CPU> m_CPU;
    std::unique_ptr<RAM> m_RAM;
};

#endif  // __GB_H__