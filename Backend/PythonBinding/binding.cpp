
#include "Board.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(python_example, m) {
    py::class_<Board>(m, "Board", py::dynamic_attr())
        .def(py::init<const int>())
        .def("placeShip", &Board::placeShip)
        .def("validShipPositions", &Board::validShipPosition)
        .def("allShipsSunk", &Board::allShipsSunk)
        .def("updateBoardHit", &Board::updateBoardHit)
        .def("shipDestroyed", &Board::shipDestroyed)
        .def("printBoardWShip", &Board::printBoardWShip)
        .def("printBoardWOShip", &Board::printBoardWOShip)
        .def("getId", &Board::getId);
}


