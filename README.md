<!-- Filename: README.md
Authors: Henrik Henriksson [Hehe0601] and Johan Karlsson [Joka1806]
Created: 2019-10-27
Course: DT042G
Description This is the Main readme file that will be used to present the project work on "Game of life" byt group 11.-->

# **Game of Life**

Game of Life, är en cellulär automat där användaren väljer en startuppställning som helt avgör hur simulationen kommer att utvecklas, enligt strikta regler. Utmaningen ligger i att hitta startuppställningar som ger intressanta utvecklingar. Game of Life är ett exempel på hur komplicerade mönster kan uppstå från väldigt enkla regler, ett fenomen som kallas emergens. Under tiden har allt fler användare skapat egna uppsättningar regler som ger unika utvecklingar.

Programmet uppfanns av John Horton Conway 1970. _[1]_

## Bakgrund

Det här projektet är det examinerande momentet i kursen DT042G \_Metoder & verktyg på Mittuniversitetet hösten 2019.

I det här projektet har som bas en fungerande implementation av programmet "Game of Life" tillhandahållits. De uppgifter som studenterna har att utföra är att kommentera, dokumentera och testa samtliga klasser i projektet. Samarbetet och arbetsfördelningen mellan gruppmedlemmarna ska skötas agilt med hjälp av verktyget Trello.

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
- -er (följt av ett regel namn) avgör vilken uppsättning regler som ska användas för jämna generationer.
- -or (följt av ett regel namn) avgör vilken uppsättning regler som ska användas för ojämna generationer.
- - Möjliga värden är för regelnamn är:

    1. conway
    2. erik
    3. von_neumann

### **Terminal/Manual build:**

Att bygga manuellt via terminalen/shell har framförallt gjorts under MacOs

 eller Ubuntu. För att skilja mellan filerna som genereras via IDEer så har
  en separat build mapp använts. Denna har då inte påverkats utav något annat program.
För att bygga projektet

    cmake ..
    make

Där det första commandot "cmake .." genererar byggfiler, kräver att
 CMakeLists filen finns lokaliserad i föräldramappen.
Efter det så byggs huvudprogrammet (GameOfLife) och test programmet
 (GameOfLife_Test) med "make" vilket kräver att programmet make finns
  installerat.
  
För att testa specifika kompilatorer kan istälet följande alternativ kunna an
ävndats

    CXX=g++ cmake ..
    make
    
Då har programmet programmet bygts med g++ istället för clan vilket är
 standard kompilatorn under MacOs systemet som använts.
     

### **Visual Studio:**

Med en installation av Visual Studio 2019 medföljer som standard kompilator Visual Studio C++ (VSC++/MSVC). Projektet öppnas enklast genom att högerklicka på dokumentroten och "Öppna i Visual Studio". Därefter ska cmake genereras, exempelvis genom att spara cmakeLists.txt. Projektet är nu redo att byggas.

Visual Studio genererar mappen "out/build" där de exekverbara filerna skapas under x-64 debug eller x64-release beroende på hur man valt att bygga projektet. För att köra applikationen med argument kan windows powershell eller git bash användas. I Windows powershell ange kommandot "start GameOfLife.exe" och ange därefter argument att köra programmet med, separerade med mellanslag. I git-bash kan programmet köras med _"./GameOfLife.exe"._

För att köra testerna i visual studio ändras kommandot till _"./GameOfLife_TEST.exe"_

### **cLion:**

För att öppna projektet väljer man open och navigerar till och väljer
projektets root map.
Efter att projektet har öppnats så skall tillgängliga byggkonfigurationer
laddas ifrån tillgängliga executables i tillgängliga CMakeLists filer.
De 2 som har varit aktuella för detta projekt är GameOfLife and
GameOfLife_Test. Vilka bygger huvudprogrammet eller testprogrammet beroende
på vilket som valts.

Den stora fördelen med att köra genom IDEn är dock att enkel kunna köra
separata testfall. Detta görs genom att öppna filen som innehåller
testfallet och klicka på den gröna pilen till vänster om SCENARIO. 
Alternativt för att köra alla testfall i en fil går det att högerklicka p
å filen och välja "Run all in [namn på den aktuella filen]"

Vid byte av branch eller om nya filer läggs till kan det behövas att h
ögerklicka på projektets CMakeList fil och välj menyalternativet "Reload
CMake project" för att uppdatera de genererade make filerna. Under vårat
arbete har det hänt att konstiga fel vid kompilering uppstått.

# Syfte

Projektet Game of Life är det avslutande momentet i kursen DT042G Metoder och verktyg i mjukvaruprojekt. Kursdeltagarna har tidigare fått genomföra laborationer och enskilda inlämningar inom områden som versionshantering, dokumentation av mjukvaruprojekt och enhetstestning med ramverket Catch.

Projektet syftar till att studenterna ska få tillämpa kunskaperna från kursens laborationer i ett något större mjukvaruprojekt.

Studenterna ska kunna visa prov på praktisk erfarenhet av:

- att versionshantera ett projekt med hjälp av GIT och ett delat remote repository på Bitbucket
- att använda byggsystemet Cmake och skapa byggscript av typen cMakeLists.txt
- att skriva enhetstester för en C++ applikation med ramverket Catch
- att skriva utförlig och omfattande dokumentation i mjukvaru projektet med hjälp av Doxygen
- att koordinera ett projekt med andra gruppmedlemmar genom den agila metoden Kanban, som planeras och administreras visa ett Trello Board.

# Genomförande

**IN PROGRESS**

Efter gruppindelningen har gruppen skapat ett Trello Bräde som baserats på ett exempel bräde tillhandahållet i kursmaterialet. Medlemmarna höll därefter en diskussion om hur arbetet smidigast kunnat läggas upp och kom överens om en grov skiss för ett arbetssätt att följa, med reservationen om att detta arbetssätt skulle komma att utvecklas under projektets gång när nya behov uppstått och nya infallsvinklar betraktats.

Den gruppmedlem som kommit fram till att en uppgift behöver genomföras skapar ett kort på Trellobrädet. Men inget krav ställs på att just den medlem som skapat kortet genomför uppgiften. Vanligast har dock blivit att den medlem som skapat kortet tagit kortet vidare från "Backlog" till "In Progress" och vidare.

Kontakt har skett genom de kanaler som Trello tillhandahåller, men främst inom de Pull Requests som en medlem skapat efter att en task är redo för review. Vi i gruppen sökte efter vägar att sammanfoga Trello med gruppens Bitbucket repository, men då denna funktionalitet kräver ett proprietärt tillägg valde vi att försöka minska redundansen på andra sätt.

Smidigast kommunikation har skett genom Discord, vilket torde te sig naturligt med hänsyn till gruppens ringa storlek. Vi har här utbytt tankar, funderingar och information. Vi har fördelat arbetet och hållit varandra uppdaterade om hur arbetet fortgått.
Vid några tillfällen har även telefonmöten ägt rum för att smidigare kunna föra 
en djupare konversation

Arbetet har utförts inom olika miljöer, vilket inte var planerat från början, men som lett till att ge en bättre insikt i hur projektet fungerar inom olika utvecklingsmiljöer. Henrik har utvecklat främst med hjälp av Visual Studio Community (VSC) på en Windowsmaskin, medan Johan har kodat med cLion på en Mac.

När en uppgift slutförts och lagts för peer review har genomgång skett i olika omfattning beroende på uppgiftens natur. Framförallt Cmakelists och kod har testats med hjälp av olika kompilatorer, manuellt och/eller med hjälp av utvecklingsmiljöerna cLion och VSC.

## Projektets faser:

### Dokumentation av klasser:

Som dokumentation räknas metadata samt beskrivning. Detta skall utföras för dokumentations uppgifter. Eftersom skrivandet av dokumentation kräver förståelse för hur klassen fungerar så kan tester läggas till som en rekommendation över vad som behöver testas.
Vad som testas läggs dock till under uppgiften att skapa tester. Finns rekommendationer så uppdateras dessa vid implementation av tester.

### Testning av klasser:

Under denna fas så skapas tester och testade funktioner dokumenteras i
respektive funktionsbeskrivning. Finns rekommendationer till tester s
å uppdateras dessa efter vad som faktiskt testas. Om buggar hittas s
å dokumenteras även de under testfasen. Det har även funnits saker som
skulle behöva ändras men som inte kan räknas som en bug. För detta har
taggen @issue använts. Om behovet av utökad funktionalitet för testning har
stödfunktioner eller hela klasser skapats. Kompilering av testerna har i sin
 tur testats under olika kompilatorer för att upptäcka eventuella fel som kan uppstå, exempelvis GCC, g++ och vc++.

## Kommunikation

Kommunikationen mellan gruppmedlemmarna har skett över tre direkta och en indirekt kanal. Huvusakligen har kommunikationen skett via en privat discord kanal. Discord har använts för snabba informella meddelanden för lättare diskutioner och uppdateringar medlemmarna mellan. För mer detaljerade diskutioner har telefonmöten hållits. Den sista direkta kanalen för kommunikation har varit innom Trello Brädet där uppgifter har lagts till och status uppdaterats med meddelanden. Kommunikationen på Trello har följt en mer formell ton på engelska. Slutligen har även bitbucket kommentarer direkt i en aktuell pull request använts som en indirekt kanal, eftersom dessa meddelanden främst meddelas via e-post.

## Namngivningskonventioner:

För att göra skapandet av trello kort och git brancher lättare att navigera igenom, framförallt när projektet fortskrider och fler och fler brancher skapats för att hantera specifika uppgifter har gruppen kommit överens om en övergripande namngivningskonvention: <typ><class><område|klassnamn>, eftersom inte alla kort berör en specifik klass utan kan vara en teknisk uppgift som berör övergripande dokumentation eller annat.

De typer som vi använt är:

- Doc: en uppift vars syfte är att dokumentera, eller förbättra existerande dokumentation
- Test: en uppgift som huvudsakligen avser implementation av tester.
- Fix/Patch: en uppgift som huvusakligen avser att uppdatera en feature eller dokumentation där denna funnits bristfällig.

I Trello har vi använt oss av de Labels som förts med från exemepel brädet, men vi har även definierat ett antal egna labels:

- Documentation - där uppgiften avser uppdatering av dokumentation
- Issue - en Label som använts för att beskriva ett problem som uppstått.
- WorkPackage - Denna Label har använts för att summera en större uppgift som har blivit uppdelad i flera mindre uppgifter.

## Metodsammanfattning

Gruppen identifierar tillsammans under diskussion uppgifter som behöver utföras, eller individuellt om behovet är uppenbart. Därefter skapas ett kort som beskriver uppgiften och varför den behöver genomföras i Trello under tabben "backlog". Den gruppmedlem som tar på sig uppgiften lägger dit sin tagg under "medlemmar" och för kortet vidare till tabben "in progress". Arbetet utförs enligt de förutsättningar som på förhand tagits fram i Trello-kortet. Om medlemmen under tiden kortet ligger i "in progress" upptäcker att uppgiften blir mer omfattande eller om förutsättningarna ändras under genomförandet, tar medlemmen ställning till om uppgiften fortfarande kan genomföras, eller om den bör delas upp i mindre "subtasks" för att inte ett enskilt kort ska bli för omfattande. Till detta syfte skapade gruppen en label för "WorkPackage" där dokumentation eller testning av en större klass kunde delas upp i mindre sub tasks som länkades in i det "övergripande" kortet för klassen. Den medlem som tar sig an en uppgift skapar en för uppgiftens utförande specifik branch med samma namn som Trello-kortet specificerat.

Eftersom nya behov uppstått under projektets gång har gruppen använt sig av labeln "Patch" för att åtgärda en större förändring i en dokumentation eller testimplementation. En mindre förändring kan om den upptäckts i ett relaterat fall, genomföras genom en enskild commit i en pågående working branch utan att ett specifikt kort och ny branch skapas för att åtgärda denna förändring.

När en uppgift är utförd pushas arbetsbranchen till gruppens repository och en pull request upprättas. Pull requesten får lämpligtvis samma namn som kortet i Trello för enklare sammanhållning. Samma gäller commits, som även kan få tillägg med beskrivande information.

Kollegan går sedan igenom materialet och lämnar eventuella synpunkter, främst direkt i pull requesten, men som ovan nämnts har vi använt direkt kommunikation via Discord för att hålla ett bättre flöde i arbetet.

Om en pull request skulle visa sig innehålla felaktigheter, eller att branchen vid review inte kan kompileras lämnas feedback på samma sätt som ovan. Medlemmen som utfört uppgiften bör då åtgärda dessa fel och uppdatera pull requesten med en ny commit. Därefter lämnas requesten åter över till kollegan för review av förändringarna.

När en pull request blivit accepterad markeras kortet som reviewat i Trello, den medlem som skapat pull Requesten mergar därefter till master, efter att ha först med git pull-kommandot försäkrat sig om att lokal master är synkroniserad med head och därmed förhindra onödiga merge konflikter.

Skulle en uppgift innehålla grova felaktigheter, finns även möjligheten att avböja en pull request. Kortet i Trello markeras då som "nekat" och uppgiften ska då återgå till Backlog tabben med en "issue" tagg som beskriver vad som är fel.

## Utvecklingsmiljöer och verktyg:

### **Henrik:**

Jag har främst utfört uppgifterna på en Windows 10 maskin, med Visual Studio Community version 16.3.5 som främsta utvecklingsmiljö. Jag har även använt mig av cLion för Windows version 2019.2.4.

De kompilatorer jag använt är VC++ som kommer som standard med Visual Studio, och MinGW-64 med GCC i cLion.

För versionshantering använder jag GIT version 2.23.0 för Windows.

För dokumentation har jag använt doxygen version 1.8.16 för Windows.

### **Johan:**

Jag har främst utfört uppgifterna på under MacOs (10.14) med cLion (2019.2.4)
men för vissa uppgifter har jag även använt terminalen. För att testa
kompabilitet har jag även testat att bygga programmen i en Virtuell Maskin
med Ubuntu 18.4

Clang är den kompilator som jag huvudsakligen har använt men har även vid
 vissa tillfällen testat med g++.
 
För versionshantering använder jag git version 2.20.1 (Apple Git-117)

För dokumentation har jag använt Doxygen version 1.8.15


## Uppkomna hinder

Vi har under projektets gång känt oss begränsade av begränsningen att
 inte kunna använda fler så kallade "power ups" som finns i Trello, bland
  annat för "work package" support och bitbucket integrering. De verktyg vi haft
   tillgång till inte kunnat integreras ordentligt, vilket har gjort det lätt för oss att ibland glömma ett steg. Exemelvis att efter att ha godkänt en pull Request i Bitbucket behöva gå över till Trello-brädet för att markera även kortet som godkänt.

Vi hade till en början svårt att få till en cMakeLists som fungerade att kompilera i olika kompilatorer. Vi fick då en möjlighet att verkligen kontrollera att vi kan kompilera koden i olika miljöer för att få allt att fungera, vissa eftergifter fick här göras, främst gällande testramverk.

Ett av problemem med cMakeLists filen var att "problemet finns inte på min
maskin". Detta ledde till svårigheter och tidsfördröjningar med att försöka
ta fram en lösning som fungerar på så många system som möjligt. Detta har
 visat på att en utvecklare själv ska kunna testa på så många system som 
 möjligt under utveckling.

Ytterligare ett hinder som kunnat uppstå är när man delat upp en större uppgift i flera små, men som är beroende av varandra, kan arbetstakten stanna av medan en medlem väntar på feedback från den andre. Som tur är har det alltid funnits mycket att göra, och Trello korten har gjort det lätt att hålla reda på var man var i en specifik uppgift.

Under testning av vissa klasser uppstod ett behov att kontrollera att något skrivits ut till terminalen, eftersom det varit funktionens uppgift. För att undvika att ovidkommande information skrivs till terminalen har outstreamen i vissa testfall "omdirigerats" till en sträng [2]. Denna sträng kan då även vid behov användas vid kontroll. Dock innehåller vissa funktioner som ska testas anrop till andra funktioner, som ändrar pekarens position eller som kör ett terminal.clear() kommando, vilket negativt påverkat utskriften av misslyckade testfall.

För att lösa detta har vi främst använt oss av det testramverk som finns i cLion och som skriver ut testresultaten i .xml format.

# Slutsatser och kommentarer

## Reflektioner Henrik

Projektet har verkligen visat på vilka problem som kan uppstå om man använder globala variabler. Själva strukturen i koden var mycket svår att följa, och det var ofta svårt att begränsa sig hur mycket man skulle kommentera koden "as-is" och inte försöka beskriva koden som den "borde vara". Här kom vår @issue tag till nytta eftersom vi då kunde kommentera på saker vi vet är "fel" men som i sig kanske inte är en bugg. Projektet har varit lärorikt i sin helhet gällande versionshantering, kommentering och skrivning av enhetstester. Jag är imponerad över att gruppen lyckats klara sig i princip utan merge konflikter genom en tydlig uppdelning av arbetet i form av tasks i Trello. Tittar man på "gitk" kommandot för projektet ser man hur omfattande det blivit.

Jag vill argumentera för att projektets syfte blivit uppfyllt, eftersom samtliga klasser i mjukvaru projektet kommenterats och testats. Vi har styrt arbetet agilt enligt en överenskommen arbetsmetod, och vi har versionshanterat projektet effektivt utan onödiga merge-konflikter.

## Reflektioner Johan

Trots att detta projekt har varit relatift litet i antalet inbalndade
personer har det visa på att det är viktigt att ha tydliga processer och att
de verktyg som används underlättar att dessa processer följs. I början av
projektet bestod arbetet mycket i att definiera hur vårat arbetsflöde skulle
se ut och hur vi underlättar för att kunna följa det. Under denna fas så 
hittaddes många "Power Ups" för trello som skulle kunna underlätta. Det 
försvårades dock pga begränsningen av att inte kunna intsalera fler "Power
Ups".<br>
Vilten och nyttan av detta arbete har senare kunnats se i form av att vi
uppfattat få problem med våran process under arbetet. Då förutom några mindre
diskusioner så har det mest förekommande problemet varit att en Pull Request
har godkännts i Bitbucket men inte uppdaterats i Trello. Vilket snabbt
medelats efter en påminnelse i Discord. <br>
Att våra processer har fungerat ganska bra har även setts då vi har jobbat
med projektet under olika tider under dagen. Då Henrik har utgått ifrån att
jobba under dagtid medan jag, Johan, mestadels har jobbat med projektet under
kvällstid. Trots detta har arbetet flytit på väl.

Vikten av att verktygen underlättar för att följa processen tycker jag även
har synliggjorts av vilka problem vi har stött på under projektet. Som
Henrik skrev så har projektet kunnat genomföras utan någon merge conflict
vilket även kan ses i form av att git som verktyg underlättar för att dela
upp uppgifter och jobba med korta arbetsflöden och kontinuerliga
uppdateringar. <br>
Det jag har saknat är möjligheten att kunna sätta upp en miljö där alla
utveklare enkelt skulle kunna genomför "smoke tests" för varje uppgift, det
vill säga att huvudprogram och framförallt för oss test programmet
går att kompilera/länka och köras. Av nyfikenhet hade det varit intresant att
testa om detta skulle gå att genomför med hjälp utav Docker men tyvärr har
inte tiden funnits för att testa ett sådant system.<br>
På samma sätt skulle det för våran situation varit bra med ett system som
kontrolerar om generering av doxygen dokumentation resulterar i några
varningar för den de klasser som ändrats i en Pull Request. Detta då det i b
örjan var väldigt många varningar tack vare alla klasser och funktioner som
inte var dokumenterade vilket gjorde att det var enkelt att missa varningar
som tillhörde de filer som vi arbetat med. 

Arbetet har varit utmanande då både dokumentation och testning båda utgår
från hur programmet är tänkt att fungera medans vi har haft tillgång till den
faktiska implementationen. Detta har i sig varit en svårighet att försöka 
avögra vad den tänkta funktionaliteten är och arbeta efter det. Där har våran
tag @issue varit till hjälp för att peka på saker som eventuellt är fel och
skulle behöva undersökas.

Slutligen skulle jag vilja instämma med henrik i att syftet med projektet har
blivit uppfyllt i form av dokumentation, tester samt arbetssätt samt att vi 
båda nog har lärt oss mycket av detta arbete. I efterhan har nog båda önskat
att denna kurs hade kommit tidigare då arbetssättet skulle ha underlättat i
programmeringskurser.  
 

## Källor

[1. Wikipedia - Conway's Game of Life (åtkomst 2019-10-27)](https://sv.wikipedia.org/wiki/Game_of_Life)

[2. Stackoverflow.com - redirect stdout/stderr to a std::string (åtkomst 2019-10-25)](https://stackoverflow.com/questions/5419356/redirect-stdout-stderr-to-a-string)
