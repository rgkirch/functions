struct Sand {
    Sand(int i) {

    }
};
struct Glass {
    Glass(Sand s) {
    }
};
int main() {
    Glass g(7);
}
