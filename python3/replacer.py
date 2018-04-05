#!/usr/bin/env python3

# parameters
# ----------
text_set = set()
filler_dict = {"mail": "test@mail.de",
               "date": "04.04.2018"}
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
        self._filled_text = str(self._text)
        fd = self.get_filler_dict()
        # for filler_key in iter(self._filler):
        for filler_key in self._filler.keys():
            print("DEBUG: filler key: '{}'".format(filler_key))

            self._filled_text = self._filled_text.replace('{{{}}}'.format(filler_key), fd[filler_key])
            print("DEBUG: filled text: '{}'".format(self._filled_text))
        return self._filled_text


if '__main__' == __name__:
    myReplacer = Replacer('Hello {name}!', {'name': 'World'})

    print(myReplacer)

    print(myReplacer.get_text())
    print(myReplacer.get_filler_dict())
    print(myReplacer.get_filled_text())
