#include <pybind11/pybind11.h>
#include "Board.h"

//https://pybind11.readthedocs.io/en/stable/classes.html

namespace py = pybind11;

PYBIND11_MODULE(class_example, m) {
    py::class_<Board>(m, "Board", py::dynamic_attr())
        .def(py::init<int>())
        .def("placeShip", &Board::placeShip)
        .def("allShipsSunk", &Board::allShipsSunk)
        .def("updateBoardHit", &Board::updateBoardHit)
        .def("shipDestroyed", &Board::shipDestroyed)
        .def("printBoardWShip", &Board::printBoardWShip)
        .def("printBoardWOShip", &Board::printBoardWOShip)
        .def("getId", &Board::getId);

}


