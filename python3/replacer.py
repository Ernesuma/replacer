#!/usr/bin/env python3

# parameters
# ----------
text_set = set()
filler_dict = {"mail":"test@mail.de",
               "date":"04.04.2018"}
text_set.add('test')


class Replacer():

    def __init__(self, text="", filler={}):
        self._text = text
        self._filler = filler
        self._filled_text = self.fill()

    def get_text(self):
        return self._text

    def get_filler_dict(self):
        return self._filler

    def get_filled_text(self):
        return self._filled_text

    def fill(self):
        self._filled_text = self._text
        for entry in self._filler.keys:
            print(entry)
            self._filled_text = self._filled_text.replace('\{{}\}'.format(entry))
        return self._text


if '__main__' == __name__:
    myReplacer = Replacer('Hello World!', {})

    print(myReplacer)

    print(myReplacer.get_text())
    print(myReplacer.get_filler_dict())
