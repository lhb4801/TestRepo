

class ManagerHandle
{
public:
    virtual ~ManagerHandle() = 0;
    
    static ManagerHandle* create(std:string name);
}
