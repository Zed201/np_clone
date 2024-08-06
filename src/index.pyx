# distutils: language = c++


from libcpp.vector cimport vector


def test():
    cdef vector[int] sh
    cdef vector[int] el

    for i in range(10):
        el.push_back(i)
    sh.push_back(3)
    sh.push_back(3)
    print(sh, el)

    m = new matrix(sh, el)
    

