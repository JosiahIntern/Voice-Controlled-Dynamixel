# NOTE: this example requires PyAudio because it uses the Microphone class
import pyaudio
import speech_recognition as sr
import serial
import time


# obtain audio from the microphone
r = sr.Recognizer() 
with sr.Microphone() as source:
    print("Say move to move the motor")
    audio = r.listen(source)

# recognize speech using Google Speech Recognition
try:
    # for testing purposes, we're just using the default API key
    # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
    # instead of `r.recognize_google(audio)`
    get = r.recognize_google(audio)
    print("Google Speech Recognition thinks you said " + get) 
except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))

ser = serial.Serial('COM8', 1000000)

time.sleep(2)



while 1:
    
    if(get == 'move'):
        frw = ser.write(b'1')
        print("Motor On")
        print(frw)
        print("Forward")
    else:
        print("Not working")





