#ifndef NONINITIALIZABLE_H
#define NONINITIALIZABLE_H

#ifndef MEP_NON_COPYABLE_H
#define MEP_NON_COPYABLE_H

namespace TOOLS {
    class NonInitializable {
    protected:
        NonInitializable() = delete;
        ~NonInitializable() = delete;
        NonInitializable(const NonInitializable& x) = delete;
        NonInitializable(NonInitializable&& x) = delete;
        NonInitializable& operator=(const NonInitializable& x) = delete;
    };
}

#endif


#endif // NONINITIALIZABLE_H
