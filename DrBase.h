Peer DrESP;
json DrData;

////Up
void analogUp(int v);
void releasedUp();
void pressedUp();
////down
void analogDown(int v);
void releasedDown();
void pressedDown();
////Left
void analogLeft(int v);
void releasedLeft();
void pressedLeft();
////Right
void analogRight(int v);
void releasedRight();
void pressedRight();
//clockwise
void pressedClock();
void analogClock(int v);
void releasedClock();
//anticlocwise
void pressedAnticlock();
void analogAnticlock(int v);
void releasedAnticlock();

//stop
void pressStop();
void releaseStop();

class DrBase
{
public:
    button *up, *down, *left, *right, *l2, *r2;
    secondaryButton *selectButton;
    int UP = 0, DOWN = 0, LEFT = 0, RIGHT = 0, C = 0, AC = 0;
    DrBase(button *up, button *down, button *left, button *right, button *l2, button *r2, secondaryButton *selectButton)
    {
        this->up = up;
        this->down = down;
        this->left = left;
        this->right = right;
        this->l2 = l2;
        this->r2 = r2;
        this->selectButton = selectButton;

        attachAll();
        storeObject();
    }
    void attachAll()
    {
        up->attachAnalogChange(analogUp);
        down->attachAnalogChange(analogDown);
        left->attachAnalogChange(analogLeft);
        right->attachAnalogChange(analogRight);
        l2->attachAnalogChange(analogClock);
        r2->attachAnalogChange(analogAnticlock);

        // up->attachPress(pressedUp);
        // down->attachPress(pressedDown);
        // left->attachPress(pressedLeft);
        // right->attachPress(pressedRight);
        // l2->attachPress(pressedClock);
        // r2->attachPress(pressedAnticlock);
        selectButton->attachPress(pressStop);

        up->attachRelease(releasedUp);
        down->attachRelease(releasedDown);
        left->attachRelease(releasedLeft);
        right->attachRelease(releasedRight);
        l2->attachRelease(releasedClock);
        r2->attachRelease(releasedAnticlock);
        selectButton->attachRelease(releaseStop);
    }
    void b_analogUp(int v)
    {
        UP = v;
        sendData("u", UP, true);
    }
    void b_analogDown(int v)
    {
        DOWN = v;
        sendData("d", DOWN, true);
    }
    void b_analogLeft(int v)
    {
        LEFT = v;
        sendData("l", LEFT, true);
    }
    void b_analogRight(int v)
    {
        RIGHT = v;
        sendData("r", RIGHT, true);
    }
    void b_analogAnticlock(int v)
    {
        AC = v;
        sendData("H", AC, true);
    }
    void b_analogClock(int v)
    {
        C = v;
        sendData("C", C, true);
    }

    // void b_pressedUp()
    // {
    //     // Semaphore++;
    //     sendData("u",UP);
    // }
    // void b_pressedDown()
    // {
    //     sendData("d",DOWN);
    // }
    void b_releasedUp()
    {
        UP = 0;
        sendData("u", UP, true);
    }
    void b_releasedDown()
    {
        DOWN = 0;
        sendData("d", DOWN, true);
    }
    void b_releasedLeft()
    {
        LEFT = 0;
        sendData("l", LEFT, true);
    }
    void b_releasedRight()
    {
        RIGHT = 0;
        sendData("r", RIGHT, true);
    }
    void b_releasedClock()
    {
        C = 0;
        sendData("C", C, true);
    }
    void b_releasedAnticlock()
    {
        AC = 0;
        sendData("H", AC, true);
    }
    void b_pressedStop()
    {
        sendData("stop", 1);
    }
    void b_releaseStop()
    {
        sendData("stop", 2);
    }
    void sendData(String name, int value, bool direct = false)
    {
        if (direct)
        {
            DrESP.sendString(name + ":" + String(char(value)));
            Serial.println(name + ":" + String(value));
        }
        else
        {
            DrData.clear();
            // DrData.addUnit(name,value);
            DrData.addUnit(name, value);
            DrESP.send(DrData);
            // DrESP.send("type","DRBASE");
            Serial.println(DrData.getString());
            Serial.println(name + "  ----   " + String(value));
            DrData.clear();
        }
    }
    void storeObject();
};

DrBase *baseObject;
DrBase db(&up, &down, &left, &right, &l2, &r2, &selectButton);

void DrBase::storeObject()
{
    baseObject = this;
}

//UP
void analogUp(int v)
{
    baseObject->b_analogUp(v);
}

void releasedUp()
{
    baseObject->b_releasedUp();
}

// void pressedUp()
// {
//     baseObject->b_pressedUp();
// }

////down
void analogDown(int v)
{
    baseObject->b_analogDown(v);
}

void releasedDown()
{
    baseObject->b_releasedDown();
}

// void pressedDown()
// {
//     baseObject->b_pressedDown();
// }

////Left
void analogLeft(int v)
{
    baseObject->b_analogLeft(v);
}

void releasedLeft()
{
    baseObject->b_releasedLeft();
}

// void pressedLeft()
// {
//     baseObject->b_pressedLeft();
// }

////Right
void analogRight(int v)
{
    baseObject->b_analogRight(v);
}

void releasedRight()
{
    baseObject->b_releasedRight();
}

// void pressedRight()
// {
//     baseObject->b_pressedRight();
// }

//clocwise
// void pressedClock(){
//     baseObject->b_pressedClock();
// }
void analogClock(int v)
{
    baseObject->b_analogClock(v);
}
void releasedClock()
{
    baseObject->b_releasedClock();
}

//anticlocwise
// void pressedAnticlock(){
//     baseObject->b_pressedAnticlock();
// }
void analogAnticlock(int v)
{
    baseObject->b_analogAnticlock(v);
}
void releasedAnticlock()
{
    baseObject->b_releasedAnticlock();
}
void pressStop()
{
    baseObject->b_pressedStop();
}
void releaseStop()
{
    baseObject->b_releaseStop();
}