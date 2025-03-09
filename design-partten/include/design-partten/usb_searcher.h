#include <iostream>

#include "searcher.h"
class UsbSearcher : public Searcher<UsbSearcher> {
    void search() {
        std::cout << "search usb device" << std::endl;
    }
};