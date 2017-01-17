
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
        //setPreviousError(error);
        //setError(getDesiredValue() - value);
        previousError = error;
        error = desiredValue - value; 
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

    int PID() {
        // premier temps ? previous time problem first time (premiere fois avec current time)
        //calcul temps courant a faire
        static float previous_time  = 0;
        static float current_time   = 0;
        
        static float integral       = 0;
        static float derivative     = 0;
        
        
        //current_time = ... timer() ...
        float dt = current_time - previous_time;
        
        //Compute integral and derivative terms based on current error.
        integral    = integral + error * dt;
        derivative  = (error-previousError) / dt;  
        
        // Prepare values for next call
        previous_time = current_time;
        
        return (KP * error) + (KI * integral) + (KD * derivative);
    }
};



