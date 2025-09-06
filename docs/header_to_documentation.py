while True:
    header = input("Paste your header or enter \"-e\" to exit:\n")
    if header == "-e": exit()

    output = ""
    current_description = None

    for line in header.split("\n"):
        if line.startswith("//"):
            current_description = line.strip("//").strip()
        elif current_description != None:
            output += f"+ `{line.strip(";").strip()}`: {current_description}\n"
            current_description = None

    print(output)