#xgettext --keyword=_ --keyword="_P:1,2" --language=C -o ../infclass-translation/infclass.pot $(find ./src -name \*.cpp -or -name \*.h)

import sys, polib, json

reload(sys)
sys.setdefaultencoding('utf-8')

def ConvertPo2Json(languageCode, plurals):
	poFileName = "../infclass-translation/infclasspot_"+languageCode+".po"
	jsonFileName = "./data/languages/"+languageCode+".json"

	po = polib.pofile(poFileName)

	f = file(jsonFileName, "w")

	print >>f, '{"translation":['

	for entry in po:
		print >>f, '\t{'
		print >>f, '\t\t"key": '+json.dumps(str(entry.msgid))+','
		if entry.msgstr:
			print >>f, '\t\t"value": '+json.dumps(str(entry.msgstr))+''
		else:
			for index in sorted(entry.msgstr_plural.keys()):
				print >>f, '\t\t"'+plurals[index]+'": '+json.dumps(entry.msgstr_plural[index])+','
		print >>f, '\t},'

	print >>f, ']}'

ConvertPo2Json("ar", ["zero", "one", "two", "few", "many", "other"])
ConvertPo2Json("es", ["one", "other"])
ConvertPo2Json("fr", ["one", "other"])
ConvertPo2Json("hu", ["one", "other"])
ConvertPo2Json("it", ["one", "other"])
ConvertPo2Json("nl", ["one", "other"])
ConvertPo2Json("pt", ["one", "other"])
ConvertPo2Json("pl", ["one", "many", "other"])
ConvertPo2Json("la", ["one", "other"])