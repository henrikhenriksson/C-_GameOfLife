<!-- Filename: README.md
Authors: Henrik Henriksson [Hehe0601] and Johan Karlsson [Joka1806]
Created: 2019-10-27
Course: DT042G
Description This is the Main readme file that will be used to present the project work on "Game of life" byt group 11.-->

# **Game of Life**

Game of Life, är en cellulär automat där användaren väljer en startuppställning som helt avgör hur simulationen kommer att utvecklas, enligt strikta regler. Utmaningen ligger i att hitta startuppställningar som ger intressanta utvecklingar. Game of Life är ett exempel på hur komplicerade mönster kan uppstå från väldigt enkla regler, ett fenomen som kallas emergens. Under tiden har allt fler användare skapat egna uppsättningar regler som ger unika utvecklingar.

Programmet uppfanns av John Horton Conway 1970. _[1]_

I det här projektet har som bas en fungerande implementation av programmet "Game of Life" tillhandahållits. De uppgifter som studenterna har att utföra är att kommentera, dokumentera och testa samtliga klasser i projektet. Sammarbetet och arbetsfördelningen mellan gruppmedlemmarna ska skötas agilt med hjälp av verktyget Trello.

## Projektmedlemmar

Henrik Henriksson _[hehe0601]_

Johan Karlsson _[joka1806]_

# **Hantering**

Instruktioner och information om hur projektet kan byggas och användas delas upp i sektioner under "Getting Started".

**IN PROGRESS**

## Getting Started:

Projektets repository klonnas med kommandot:

    git clone -recursive git@bitbucket.org:miun_dt042g/group_11_ht19_project.git

Glöm inte flaggan _-recursive_ eftersom biblioteket "Terminal" ingår som en submodule till projektet.

Därefter väljs en byggmiljö. Byggning av det här projektet har testats manuellt, inom Visual Studio Community 2019 och cLion. När projektet byggts med ett av verktygen nedan ska två exekverbara filer ha genererats, en för körning av tester och en för körning av programmet "Game of Life".

Programmet kan nu köras genom att starta programmet genom terminalen och ange något av följande argument:

- -h för helpscreen
- -g (följt av en siffra) för antalet generationer att köra
- -s (följt av dimensioner i formatet breddxhöjd) för storleken på världen. Programmet är inte lämpat för större dimensioner än 80x24 i en vanlig terminal.
- -f (namn på fil) för att läsa direkt från fil. Ange filens sökväg som värde.
- -er (följt av ett regelnamn) avgör vilken uppsättning regler som ska användas för jämna generationer.
- -or (följt av ett regelnamn) avgör vilken uppsättning regler som ska användas för ojämna generationer.
- - Möjliga värden är för regelnamn är:

    1. conway
    2. erik
    3. von_neumann

### **Terminal/Manual build:**

TODO

### **Visual Studio:**

Med en installation av Visual Studio 2019 medföljer som standard kompilator Visual Studio C++ (VSC++/MSVC). Projektet öppnas enklast genom att högerklicka på dokumentroten och "Öppna i Visual Studio". Därefter ska cmake genereras, exempelvis genom att spara cmakeLists.txt. Projektet är nu redo att byggas.

Visual Studio genererar mappen "out/build" där de exekverbara filerna skapas under x-64 debug eller x64-release beroende på hur man valt att bygga projektet. För att köra applikationen med argument kan windows powershell eller git bash användas. I Windows powershell ange kommandot "start GameOfLife.exe" och ange därefter argument att köra programmet med, separerade med mellanslag. I git-bash kan programmet köras med "./GameOfLife.exe".

_TODO: Köra programmet med argument direkt från VS._

### **cLion:**

TODO

# Syfte

Projektet Game of Life är det avslutande momentet i kursen DT042G Metoder och verktyg i mjukvaruprojekt. Kursdeltagarna har tidigare fått genomföra laborationer och enskilda inlämningar inom områden som versionshantering, dokumentation av mjukvaruprojekt och enhetstestning med ramverket Catch.

Projektet syftar till att studenterna ska få tillämpa kunspakerna från kursens laborationer i ett något större mjukvaruprojekt.

Studenterna ska kunna visa prov på praktisk erfarenhet av:

- att versionshantera ett projekt med hjälp av GIT och ett delat remote repository på Bitbucket
- att använda byggsystemet Cmake och skapa byggscript av typen cMakeLists.txt
- att skriva enhetstester för en C++ applikaiton med ramverket Catch
- att skriva utförlig och omfattande dokumentation i mjukvaruprojektet med hjälp av Doxygen
- att koordinera ett projekt med andra gruppmedlemmar genom den agila metoden Kanban, som planeras och administreras visa ett Trello Board.

# Genomförande

**IN PROGRESS**

Efter gruppindelningen har gruppen skapat ett Trello Bräde som baserats på ett exempelbräde tillhandahållet i kursmaterialet. Medlemmarna höll därefter en diskussion om hur arbetet smidigast kunnat läggas upp och kom överens om en grov skiss för ett arbetssätt att följa, med reservationen om att detta arbetssätt skulle komma att utvecklas under projektets gång när nya behov uppstått och nya infallsvinklar betraktats.

Den gruppmedlem som kommit fram till att en uppggift behöver genomföras skapar ett kort på Trellobrädet. Men inget krav ställs på att just den medlemen som skapat kortet genomför uppgiften. Vanligast har dock blivit att den medlem som skapat kortet tagit kortet vidare från "Backlog" till "In Progress" och vidare.

Kontakt har skett genom de kanaler som Trello tillhandahåller, men främst inom de Pull Requests som en medlem skapat efter att en task är redo för review. Vi i gruppen sökte efter vägar att sammanfoga Trello med gruppens Bitbucket repository, men då denna funktionalitet kräver ett proprietärt tillägg valde vi att försöka minska redundansen på andra sätt.

Smidigast kommunikation har skett genom Discord, vilket torde te sig naturligt med hänsyn till gruppens ringa storlek. Vi har här utbytt tankar, funderingar och information. Vi har fördelat arbetet och hållit varandra uppdaterade om hur arbetet fortgått.

Arbetet har utförts inom olika miljöer, vilket inte var planerat från början, men som lett till att ge en bättre insikt i hur projektet fungerar inom olika utvecklingsmiljöer. Henrik har utvecklat främst med hjälp av Visual Studio Community (VSC) på en Windowsmaskin, medan Johan har kodat med cLion på en Mac.

När en uppgift slutförts och lagts för peer review har genomgång skett i olika omfattning beroende på uppgiftens natur. Framförallt Cmakelists och kod har testats med hjälp av olika kompilatorer, manuellt och/eller med hjälp av utvecklingsmiljöerna cLion och VSC.

## Utvecklingsmiljöer och verktyg:

### **Henrik:**

Jag har främst utfört uppgifterna på en Windows 10 maskin, med Visual Studio Community version 16.3.5 som främsta utvecklingsmiljö. Jag har även använt mig av cLion för Windows version 2019.2.4.

De kompilatorer jag använt är VC++ som kommer som standard med Visual Studio, och MinGW-64 med GCC i cLion.

För versionshantering använder jag GIT version 2.23.0 för Windows.

För dokumentation har jag använt doxygen version 1.8.16 för Windows.

### **Johan:**

# Diskussion

## (gemensam)

## Uppkomna hinder

# Slutsatser och kommentarer

## Reflektioner Henrik

## Reflektioner Johan

**IN PROGRESS**

## Källor

[1. Wikipedia - Conway's Game of Life](https://sv.wikipedia.org/wiki/Game_of_Life)
