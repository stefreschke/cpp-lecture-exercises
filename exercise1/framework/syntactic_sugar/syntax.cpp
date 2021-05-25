
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <sstream>

// You may edit / add anything from here to satisfy the interfaces and behaviors expected by the execution code below

struct Currency
{
    unsigned long long int cents;

    Currency operator+(Currency rhs) {
        Currency newCurrency = Currency();
        newCurrency.cents = rhs.cents + cents;
        return newCurrency;
    }

    Currency operator, (Currency rhs) {
        return operator+(rhs);
    }

    friend Currency operator &&(Currency lhs, Currency rhs) {
        return lhs + rhs;
    }

    friend bool operator==(Currency lhs, int rhs) {
        return lhs.cents == rhs;
    }

    friend void operator+= (Currency& lhs, Currency rhs) {
        lhs.cents += rhs.cents;
    }

    friend void operator-= (Currency& lhs, Currency rhs) {
        lhs.cents -= rhs.cents;
    }
};

constexpr Currency operator"" _euro (unsigned long long value) {
    Currency c = Currency();
    c.cents = 100 * value;
    return c;
}

constexpr Currency operator"" _cents (unsigned long long value) {
    Currency c = Currency();
    c.cents = value;
    return c;
}

constexpr Currency operator"" _cent (unsigned long long value) {
    return operator""_cents(value);
}

namespace Bills
{
    const auto Five = Currency { 500 };
    const auto Ten = Currency { 1000 };
    const auto Twenty = Currency { 2000 };
    const auto Fifty = Currency { 5000 };
}

struct Account
{
    Currency balance = 0_euro;

    explicit Account(const Currency & balance)
    : balance(balance)
    {
    }
};

std::ostream& operator<<(std::ostream& os, const Account& a) {
    int euros = a.balance.cents * 1.0 / 100;
    int cents = a.balance.cents % 100;
    os << "Account with balance " << euros << " euro, " << cents << " cents";
    return os;
}

struct Transaction {
    Account* from;
    Account* to;
    Currency amount;
    void apply() const {
        from->balance -= amount;
        to->balance += amount;
    }
};

Transaction operator>>(Account& account, Currency currency) {
    auto trans = Transaction();
    trans.from = &account;
    trans.amount = currency;
    return trans;
}

void operator>>(Transaction trans, Account& other) {
    trans.to = &other;
    trans.apply();
}

Transaction operator<<(Account& account, Currency currency) {
    auto trans = Transaction();
    trans.to = &account;
    trans.amount = currency;
    return trans;
}

void operator<<(Transaction trans, Account& other) {
    trans.from = &other;
    trans.apply();
}

struct Object
{
public:
    Object(float value, bool count);
    ~Object();
    
    operator float() const { return m_value; }
    
    float m_value;
};

struct Converter
{
    float m_value;
    
    operator float() const { return float(m_value); }
    operator Object() const { return Object{ m_value, true }; }
};


struct Generator
{
    float createFloat() {
        return 1337.42;
    }

    Object createObject() {
        return Object(rand(), true);
    }

    class Proxy
    {
        Generator * proxied;
    public:
        explicit Proxy(Generator* actualGenerator) {
            proxied = actualGenerator;
        }
        // this just seems so silly
        // ...thx for the hint in the forum :)
        operator float() const
        {
            return proxied->createFloat();
        }
        operator Object() const
        {
            return proxied->createObject();
        }

        static size_t objectInstanceCount;
    };

    static size_t objectInstanceCount;

    // gen()
    Proxy operator()()
    {
        return Proxy{this};
    }


};

struct MatrixCell {
    float value;
    int x;
    int y;

    MatrixCell(int newX, int newY) {
        x = newX;
        y = newY;
    }
};

struct MatrixSelection {
    std::vector<std::pair<int, int>> ids;
    std::vector<MatrixCell*> cells;

    MatrixSelection& operator=(float value) {
        for (auto cell : cells) {
            cell->value = value;
        }
    }
};

enum MatrixDimensionType {X_DIMENSION, Y_DIMENSION};

struct MatrixDimension {
    MatrixDimensionType dimType;

    explicit MatrixDimension(MatrixDimensionType newDimType) {
        dimType = newDimType;
    }

    friend MatrixSelection operator== (const MatrixDimension &lhs, int value) {
        MatrixSelection selection;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (lhs.dimType == X_DIMENSION) {
                    if (x == value) {
                        selection.ids.emplace_back(x, y);
                    }
                } else {
                    if (y == value) {
                        selection.ids.emplace_back(x, y);
                    }
                }
            }
        }
        return selection;
    }

    friend MatrixSelection operator== (const MatrixDimension &lhs, const MatrixDimension &rhs) {
        MatrixSelection selection;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (lhs.dimType == X_DIMENSION) {
                    if (rhs.dimType == X_DIMENSION) {
                        selection.ids.emplace_back(x, y);
                    } else {
                        if (x == y) {
                            selection.ids.emplace_back(x, y);
                        }
                    }
                } else {
                    if (rhs.dimType == Y_DIMENSION) {
                        selection.ids.emplace_back(x, y);
                    } else {
                        if (x == y) {
                            selection.ids.emplace_back(x, y);
                        }
                    }
                }
            }
        }
        return selection;
    }

    friend MatrixSelection operator< (const MatrixDimension &lhs, const MatrixDimension &rhs) {
        MatrixSelection selection;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (lhs.dimType == X_DIMENSION) {
                    if (rhs.dimType == X_DIMENSION) {
                        // do nothing
                    } else {
                        if (x < y) {
                            selection.ids.emplace_back(x, y);
                        }
                    }
                } else {
                    if (rhs.dimType == Y_DIMENSION) {
                        // do nothing
                    } else {
                        if (y < x) {
                            selection.ids.emplace_back(x, y);
                        }
                    }
                }
            }
        }
        return selection;
    }

    friend MatrixSelection operator> (const MatrixDimension &lhs, const MatrixDimension &rhs) {
        MatrixSelection selection;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (lhs.dimType == X_DIMENSION) {
                    if (rhs.dimType == X_DIMENSION) {
                        // do nothing
                    } else {
                        if (x > y) {
                            selection.ids.emplace_back(x, y);
                        }
                    }
                } else {
                    if (rhs.dimType == Y_DIMENSION) {
                        // do nothing
                    } else {
                        if (y > x) {
                            selection.ids.emplace_back(x, y);
                        }
                    }
                }
            }
        }
        return selection;
    }
};

struct WeirdCoordinateLiteral {
    int row;
    MatrixDimensionType dimensionType;
};

MatrixSelection operator , (WeirdCoordinateLiteral a, WeirdCoordinateLiteral b) {
    MatrixSelection s = MatrixSelection();
    if (a.dimensionType == X_DIMENSION) {
        s.ids.emplace_back(a.row, b.row);
    } else {
        s.ids.emplace_back(b.row, a.row);
    }
    return s;
};

constexpr WeirdCoordinateLiteral operator"" _x (unsigned long long deg) {
    WeirdCoordinateLiteral redux = WeirdCoordinateLiteral();
    redux.dimensionType = X_DIMENSION;
    redux.row = deg;
    return redux;
}

constexpr WeirdCoordinateLiteral operator"" _y (unsigned long long deg) {
    WeirdCoordinateLiteral redux = WeirdCoordinateLiteral();
    redux.dimensionType = Y_DIMENSION;
    redux.row = deg;
    return redux;
}

struct Matrix
{
    MatrixDimension x = MatrixDimension(X_DIMENSION);
    MatrixDimension y = MatrixDimension(Y_DIMENSION);

    Matrix()
    {
        initCells();
    }

    Matrix(std::initializer_list<float> initializer)
    {
        initCells();
        readInitList(initializer);
    }

    friend bool operator== (const Matrix &lhs, const Matrix &rhs) {
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (lhs.m_c[x][y].value != rhs.m_c[x][y].value) {
                    return false;
                }
            }
        }
        return true;
    }

    MatrixSelection operator[] (MatrixSelection selection) {
        for (auto pair : selection.ids) {
            selection.cells.push_back(&m_c[pair.second][pair.first]);
        }
        return selection;
    }


protected:
    static const int size{16};
    std::vector<std::vector<MatrixCell>> m_c;

private:
    void initCells() {
        for (int y = 0; y < 4; y++) {
            std::vector<MatrixCell> rows;
            for (int x = 0; x < 4; x++) {
                MatrixCell cell = MatrixCell(x, y);
                cell.value = 0.0;
                rows.push_back(cell);
            }
            m_c.push_back(rows);
        }
    }
    void readInitList(std::initializer_list<float> &initializer) {
        int x = 0;
        int y = 0;
        for (auto value : initializer)
        {
            m_c[x][y++].value = value;
            if (y == 4) {
                x++;
                y = 0;
            }
        }
    }
};

// End of solution
// Do not edit the source code below!

// Generator::objectInstanceCount must be incremented on object creation and shall never be manipulated otherwise
Object::Object(float value, bool count) : m_value(value) { if (count) Generator::objectInstanceCount++; }
Object::~Object() {}
size_t Generator::objectInstanceCount = 0;

void generator()
{
    Generator gen;
    std::vector<float> floats;
    std::vector<Object> objects;
	
    assert(objects.size() == Generator::objectInstanceCount);

    for (auto i = 0; i < 500; ++i)
    {
        if (i % 7 == 0)
        {
            floats.emplace_back(gen());
        }
        else if (i % 5 == 0)
        {
            objects.emplace_back(gen());
        }
        else
        {
            std::cout << gen() << std::endl;
        }
    }
    
    assert(objects.size() == Generator::objectInstanceCount);
}

void accounting()
{
    Account a { 200_euro and 34_cents };
    Account b { 300_euro and 1_cent };

    b >> (100_euro, 32_cents) >> a;

    assert(a.balance == 30066);
    assert(b.balance == 19969);

    b << Bills::Fifty << a;

    assert(a.balance == 25066);
    assert(b.balance == 24969);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::stringstream stream_a;
    stream_a << a;
    std::stringstream stream_b;
    stream_b << b;
    assert(stream_a.str() == "Account with balance 250 euro, 66 cents");
    assert(stream_b.str() == "Account with balance 249 euro, 69 cents");
}

void matrix()
{
    Matrix m;
    
    Matrix m1 = { 0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0 };
    assert(m == m1);
    
    m[m.y == m.x] = 1.0f;
    
    Matrix m2 = { 1, 0, 0, 0,   0, 1, 0, 0,   0, 0, 1, 0,   0, 0, 0, 1 };
    assert(m == m2);
    
    m[m.y > m.x] = 3.0f;
    
    Matrix m3 = { 1, 0, 0, 0,   3, 1, 0, 0,   3, 3, 1, 0,   3, 3, 3, 1 };
    assert(m == m3);
    
    m[m.y < m.x] = 4.0f;
    
    Matrix m4 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 4,   3, 3, 3, 1 };
    assert(m == m4);
    
    m[3_y, 2_x] = 12.0f;

    Matrix m5 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 4,   3, 3, 12, 1 };
    assert(m == m5);

    m[3_x, 2_y] = 42.0f;

    Matrix m6 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 42,   3, 3, 12, 1 };
    assert(m == m6);

    m[m.y == 0] = 2.0f;

    Matrix m7 = { 2, 2, 2, 2,   3, 1, 4, 4,   3, 3, 1, 42,   3, 3, 12, 1 };
    assert(m == m7);
}

int main(int argc, char * argv[])
{
    matrix();
    accounting();
    generator();
    return 0;
}
