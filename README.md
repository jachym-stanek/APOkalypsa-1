# APOkalypsa
Seminary work for the APO subject in summer semester of 2020. The PONG game on MZapo platform.

## Team
Hynek "APOmaster" Zamazal

Jachym "Hekr" Stanek

## Stash dotazů pro Píšu

Zatím nemáme žádné dotazy

# Užitečné věci

## git

Nějaký užitečný příkazy k používání GITu.

### synchronizace forku

Před začátkem práce je dobrý, abysme oba měli u sebe to samý. Na to je dobrá tahle sekvence příkazů:

0. **Nemít rozdělanou žádnou práci, během tohohle procesu je dost snadný o ní přijít!**
1. `git checkout master` - ujisti se, že jsi ve svojí hlavní branchy
2. `git pull` - synchronizuj si to, co máš u sebe na počítači s tim, co je na serveru
3. `git checkout [tvoje branch]` - přepni na branch `[tvoje branch]`
4. `git pull`  - synchronizuj si to, co máš u sebe na počítači s tim, co je na serveru
5. `git rebase master` - sesynchronizuj is `[tvojí branch]` s masterem
6. `git push` - pošli sesynchronizovanou `[tvojí branch]` na server, ať je všude to samý
6. `git checkout master` - přepni do `masteru`
7. `git fetch upstream` - stáhni data z hlavního repozitáře
8. `git merge upstream/master` - spoj svůj `master` se staženejma datama z hlavního repozitáře
9. `git push`
10. `git checkout [tvoje branch]` - přepni se od `[svojí branche]`
11. `git rebase master` - synchronizuj si `[svojí branch]` se svym `masterem`
12. `git push` - pošli sesynchronizovanou branch na server, ať je všude to samý

### commit

Pro odeslání změn na server je potřeba je commitnout

1. `git add [složka soubory... prostě to, co chceš přidat]` - přidej soubory do commitu
2. `git commit -m "[Nějaká message o tom, co jsi udělal]"` - uložení commitu
3. `git push` - poslání commitu na server

### vytvořit novou branch

Branche jsou dobrý na separování vývoje různejch funkcionalit

1. `git checkout [existující branch]` - přepni se od branche, ze který chceš, aby ta nová vycházela (nejčastěji `master`)
2. `git branch [jméno nový branche]` - vytvoř `[novou branch]`
3. `git checkout [nová branch]` - přepni se do `[nový branche]`
4. `git push -u origin [nová branch]` - založ na serveru `[novou branch]` a pošli do ní soubory

## Markdown

Cheat-sheat k markdownu je třeba [tady](https://guides.github.com/features/mastering-markdown/), je to fakt typu easy.

