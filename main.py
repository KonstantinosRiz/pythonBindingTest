from MyModule import Example

def main():
    # 2 random numbers chosen, could be read from standard input if needed
    randomNumber1 = 5.0
    randomNumber2 = 9.0
    myObject = Example(randomNumber1, randomNumber2)
    result = myObject.add()
    print("My result is:", result)

if __name__ == '__main__':
    main()