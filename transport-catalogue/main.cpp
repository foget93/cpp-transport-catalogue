#include "input_reader.h"
#include "transport_catalogue.h"

using namespace std;
using namespace transport_catalogue;
using namespace query;

int main() {
    TransportCatalogue tc;
    InputReader ir;

    ir.ParseInput(cin);
    ir.ParseInput(cin);

    ir.Load(cout, tc);
    return 0;
}
