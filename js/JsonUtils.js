function convertListModelToJson(model)
{
    var jsonModel = []
    for (var i = 0; i < model.count; ++i) {
        jsonModel[i] = model.get(i)
    }

    return JSON.stringify(jsonModel)
}
