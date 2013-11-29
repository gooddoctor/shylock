#include "data.h"

#include <stdexcept>
#include <map>
#include <algorithm>
#include <iterator>

class TiXmlIterator : public std::iterator<std::input_iterator_tag, TiXmlElement> {
private:
    TiXmlElement* root;
public:
    TiXmlIterator(TiXmlElement* rt) :
          root(rt) { }

    TiXmlIterator() :
          root(0) { }

    TiXmlIterator(const TiXmlIterator& iter) :
          root(iter.root) { }

    TiXmlIterator& operator++() {
        root = static_cast<TiXmlElement*>(root->NextSibling());
        return *this;
    }

    TiXmlIterator operator++(int) {
        TiXmlIterator temp(*this);
        operator++();
        return temp;
    }

    bool operator==(const TiXmlIterator& rhs) {
        return root == rhs.root;
    }

    bool operator!=(const TiXmlIterator& rhs) {
        return root != rhs.root;
    }


    TiXmlElement* operator->() {
        return root;
    }

    TiXmlElement& operator*() {
        return *root;
    }
};

std::list<data::XML*> data::XML::all_of_them;

// data::XML* data::find(const engine::String& id) {
//     using iter = std::list<data::XML*>::iterator;
//     iter win_pos = std::find_if(data::XML::all_of_them.begin(), 
//                                 data::XML::all_of_them.end(),
//                                 [&id](data::XML* entry) -> bool {
//                                     return entry->id == id;
//                                 });
//     assert(win_pos != data::XML::all_of_them.end());
//     return *win_pos;
// }

data::XML::XML(TiXmlDocument* db_value, const engine::String& id_value) : 
      db(db_value), id(id_value) {
    all_of_them.push_back(this);
}

template <>
data::XML* data::XML::insert<data::TOP>(std::map<engine::String, engine::String> entry) {
    assert(db);
    TiXmlElement item("entity");
    std::for_each(entry.begin(), entry.end(), 
                 [&item](const std::pair<engine::String, engine::String>& attr) {
                     item.SetAttribute(attr.first.mb_str(), attr.second.mb_str());
                 });
    db->FirstChild("shylock")->InsertEndChild(item);
    assert(db->SaveFile());
    return this;
}

template <>
data::XML* data::XML::insert<data::CHILD>(std::map<engine::String, engine::String> parent,
                                          std::map<engine::String, engine::String> child) {
    assert(db);
    auto contains = [](TiXmlElement& node, const std::pair<engine::String, engine::String>& attr) {
        return ((node.Attribute(attr.first.mb_str()) != nullptr) && 
                (engine::String::FromUTF8(node.Attribute(attr.first.mb_str())) == attr.second));
    };

    //find parent position
    TiXmlIterator parent_pos = 
        std::find_if(TiXmlIterator(db->RootElement()->FirstChildElement()), TiXmlIterator(),
                     [&parent, &contains](TiXmlElement& node) {
                         using iter = std::map<engine::String, engine::String>::iterator;
                         for (iter it = parent.begin(); it != parent.end(); it++) {
                             if (!contains(node, *it))
                                 return false;
                         }
                         return true;
                     });
    assert(parent_pos != TiXmlIterator());

    //create xml child
    TiXmlElement item("payment");
    std::for_each(child.begin(), child.end(), 
                  [&item](const std::pair<engine::String, engine::String>& attr) {
                     item.SetAttribute(attr.first.mb_str(), attr.second.mb_str());
                 });

    //insert it
    parent_pos->InsertEndChild(item);
    assert(db->SaveFile());
    
    return this;
}

template <>
data::XML* data::D(engine::String id, engine::String path) {
    if (FILE* file = fopen(path.mb_str(), "r")) {
        fclose(file);
        TiXmlDocument* db = new TiXmlDocument(path.mb_str());
        assert(db->LoadFile());
        return new data::XML(db, id);
    } else {
        TiXmlDocument* db = new TiXmlDocument(path.mb_str());
        db->Parse("<?xml version=\"1.0\" standalone=\"no\" ?>"
                  "<shylock>"
                  "</shylock>");
        assert(db->SaveFile());
        return new data::XML(db, id);
    }
    return 0;
}

template <>
data::XML* data::D(engine::String id) {
    using iter = std::list<data::XML*>::iterator;
    iter xml_pos = std::find_if(data::XML::all_of_them.begin(), 
                                data::XML::all_of_them.end(),
                                [&id](data::XML* entry) -> bool {
                                    return entry->id == id;
                                });
    assert(xml_pos != data::XML::all_of_them.end());
    return *xml_pos;
}

template <>
data::XML* data::D(const wchar_t* id) {
    return data::D<XML*>(engine::String(id));
}

template <>
data::RUN data::D(std::function<bool(void)> callback, int argc, char** argv) {
    callback();
    return data::RUN();
}


