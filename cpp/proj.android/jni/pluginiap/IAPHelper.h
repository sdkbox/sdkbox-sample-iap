/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/

#ifndef _IAPHELPER_H_
#define _IAPHELPER_H_

#include <vector>
#include <string>
#include "PluginIAP.h"
#include "json98.h"

namespace sdkbox
{
    class Json;

    // creates a product from the SDKBOX config jsonToProduct
    // Only the id and consumable fields are needed to create
    // a valid product, the rest of the fields are filled in.
    Product configToProduct(const Json& j);

    // convert products to and from json format.
    Product jsonToProduct(const Json& j);
    Json productToJson(const Product& product);

    // convert arrays of products to and from json format.
    std::vector<Product> jsonToProducts(const std::string& j);
    Json productsToJson(const std::vector<Product>& products);
}

#endif
