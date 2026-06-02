
#include <iostream>
#include <cmath>
#include <algorithm> // Для std::min

            using namespace std;

class Triangle {
    double a, b, c;
    int color;

public:
    // Конструктор за замовчуванням
    Triangle() : a(1), b(1), c(1), color(0) {}

    // Конструктор з параметрами: спочатку даємо безпечні значення, потім перевіряємо
    Triangle(double a, double b, double c, int color = 0) : a(1), b(1), c(1), color(0) {
        setSides(a, b, c);
        setColor(color);
    }

    void setSides(double a, double b, double c) {
        if (a > 0 && b > 0 && c > 0 &&
            a + b > c && a + c > b && b + c > a) {
            this->a = a;
            this->b = b;
            this->c = c;
        }
        else {
            cout << "Error: incorrect triangle. Keeping previous/default values.\n";
        }
    }

    void setColor(int c) {
        if (c >= 0) color = c;
        else cout << "Error: wrong color\n";
    }

    double getA() { return a; }
    double getB() { return b; }
    double getC() { return c; }
    int getColor() { return color; }

    double perimeter() {
        return a + b + c;
    }

    double area() {
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    void print() {
        cout << "\nTriangle: ";
        cout << "a=" << a << " b=" << b << " c=" << c;
        cout << " color=" << color;
        cout << " P=" << perimeter();
        cout << " S=" << area() << endl;
    }
};

class VectorLong {
    long* arr;
    int size;
    int state;
    static int count;

public:
    VectorLong() {
        size = 1;
        arr = new long[size] {0};
        state = 0;
        count++;
    }

    VectorLong(int n) {
        if (n <= 0) {
            size = 0;
            arr = nullptr;
            state = -1;
        }
        else {
            size = n;
            arr = new long[size] {0};
            state = 0;
        }
        count++;
    }

    VectorLong(int n, long value) {
        if (n <= 0) {
            size = 0;
            arr = nullptr;
            state = -1;
        }
        else {
            size = n;
            arr = new long[size];
            for (int i = 0; i < size; i++)
                arr[i] = value;
            state = 0;
        }
        count++;
    }

    VectorLong(const VectorLong& v) {
        size = v.size;
        if (size > 0) {
            arr = new long[size];
            for (int i = 0; i < size; i++)
                arr[i] = v.arr[i];
        }
        else {
            arr = nullptr;
        }
        state = v.state;
        count++;
    }

    VectorLong& operator=(const VectorLong& v) {
        if (this != &v) {
            delete[] arr;
            size = v.size;
            if (size > 0) {
                arr = new long[size];
                for (int i = 0; i < size; i++)
                    arr[i] = v.arr[i];
            }
            else {
                arr = nullptr;
            }
            state = v.state;
        }
        return *this;
    }

    ~VectorLong() {
        delete[] arr;
        count--;
    }

    void set(int i, long val = 0) {
        if (i >= 0 && i < size)
            arr[i] = val;
        else
            state = -2;
    }

    long get(int i) {
        if (i >= 0 && i < size)
            return arr[i];
        state = -2;
        return 0;
    }

    // Змінено на const VectorLong&
    VectorLong add(const VectorLong& v) {
        int n = min(size, v.size);
        VectorLong res(n);
        for (int i = 0; i < n; i++)
            res.arr[i] = arr[i] + v.arr[i];
        return res;
    }

    // Змінено на const VectorLong&
    VectorLong sub(const VectorLong& v) {
        int n = min(size, v.size);
        VectorLong res(n);
        for (int i = 0; i < n; i++)
            res.arr[i] = arr[i] - v.arr[i];
        return res;
    }

    VectorLong mul(unsigned int k) {
        VectorLong res(size);
        for (int i = 0; i < size; i++)
            res.arr[i] = arr[i] * k;
        return res;
    }

    // Змінено на const VectorLong&
    bool isLess(const VectorLong& v) {
        for (int i = 0; i < min(size, v.size); i++)
            if (arr[i] >= v.arr[i]) return false;
        return true;
    }

    void print() {
        cout << "Vector: ";
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    static int getCount() {
        return count;
    }
};

int VectorLong::count = 0;

int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1 - Triangle (Demo)\n";
        cout << "2 - Vector (Demo)\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";

        // Перевірка на коректність вводу, щоб уникнути зациклювання при введенні літер
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            cout << "\n--- Testing Triangle ---\n";
            Triangle t1(3, 4, 5, 1);
            t1.print();

            Triangle t2(1, 1, 10); // Некоректний трикутник
            t2.print();
            break;
        }
        case 2: {
            cout << "\n--- Testing Vector ---\n";
            VectorLong v1(3, 5);
            VectorLong v2(3, 2);
            v1.print();
            v2.print();

            VectorLong v3 = v1.add(v2);
            cout << "Sum ";
            v3.print();
            break;
        }
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Wrong option! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
