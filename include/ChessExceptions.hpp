#pragma once
#include <exception>
#include <string>

class ChessException : public std::exception {
    std::string _msg;
public:
    explicit ChessException(std::string msg) : _msg(std::move(msg)) {}
    const char* what() const noexcept override { return _msg.c_str(); }
};

class InvalidMoveException : public ChessException {
public:
    explicit InvalidMoveException(const std::string& msg)
            : ChessException("Invalid move: " + msg) {}
};

class EmptyPriorityQueueException : public ChessException {
public:
    EmptyPriorityQueueException() : ChessException("PriorityQueue is empty") {}
};

class PawnPromotionException : public ChessException {
public:
    explicit PawnPromotionException(const std::string& msg)
            : ChessException("Pawn promotion: " + msg) {}
};
