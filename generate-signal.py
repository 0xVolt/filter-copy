import wave
import struct

def wavToFloat(wave_file):
    w = wave.open(wave_file)
    astr = w.readframes(w.getnframes())
    
    # convert binary chunks to short 
    a = struct.unpack("%ih" % (w.getnframes() * w.getnchannels()), astr)
    
    # a = [float(val) / pow(2, 15) for val in a]
    a = [float(val) for val in a]
    
    return a


def writeSignal(signal, signalLength):
    outputFile = open('data/signal.txt', 'w')
    
    outputFile.write(f'{signalLength}\n')
    
    for index, dataPoint in enumerate(signal):
        outputFile.write(f'{index} {dataPoint}\n')
        
    outputFile.close()


def main():
    signal = wavToFloat(r'data/wrong-place-sound.wav')
    
    signalLength = len(signal)
    
    print("# Frames Read:", len(signal))
    print(f"Range of Values: [{str(min(signal))}, {str(max(signal))}]")
    print(type(signal))
    
    writeSignal(signal, signalLength)

    print("Generated signal written to output file!")

if __name__ == '__main__':
    main()