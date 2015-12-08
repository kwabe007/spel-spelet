#ifndef PARTY_HPP
#define PARTY_HPP


class Party {
private:
    std::string name;
    std::vector<Entity*> members;
public:
    void add_member(Entity& new_member);
    std::size_t size() const;

};

#endif
