
#define KP 0.1
#define KI 0.05
#define KD 0.01

class MotorPID {    
    float desiredValue = 0;
    float error = 0;
    float previousError = 0;
    
public:
    float getDesiredValue() {
      return desiredValue;
    }

    void setDesiredValue(float value) {
      desiredValue = value;
    }
    
    void newValue(float value) {        
        setPreviousError(error);
        setError(getDesiredValue() - value);
    }
    
    void setError(float error_) {
        error = error_;
    }
    
    float getError() {
        return error;
    }
    
    float getPreviousError() {
        return previousError;
    }
    
    float setPreviousError(float previousError_) {
        previousError = previousError_;
    }

    int PID(float integral, float dt) {
      return KP * getError() + (KI * integral * dt) + (KD * getPreviousError() /dt);
    }
};



