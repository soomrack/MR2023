import sys
import os
import pandas as pd

from typing import List, Tuple


def data_cleaner(csv_path:str) -> Tuple[pd.DataFrame]:
    
    df = pd.read_csv(csv_path)

    required_columns:List = ["AIR_TIME", "ORIGIN_CITY_NAME", "DEST_CITY_NAME"]
    all_columns:List = df.columns.tolist()
    to_delete:List = list(set(all_columns).difference(set(required_columns)))

    cleared_data:pd.DataFrame = df.dropna().drop(to_delete, axis=1)
    cleared_data.drop(cleared_data[cleared_data["DEST_CITY_NAME"] == cleared_data["ORIGIN_CITY_NAME"]].index, inplace=True)
    cleared_data.drop(cleared_data[cleared_data["AIR_TIME"] <= 0].index, inplace=True)
    cleared_data.reset_index(inplace=True, drop=True)

    origin_city_names:List = cleared_data["ORIGIN_CITY_NAME"].drop_duplicates().tolist()
    dest_city_names:List = cleared_data["DEST_CITY_NAME"].drop_duplicates().tolist()
    all_possible_city_names:List = list(set(origin_city_names).union(set(dest_city_names)))

    cities_df:pd.DataFrame = pd.DataFrame({"City": all_possible_city_names})

    return cleared_data, cities_df
    
    

def save_cleared_data(cleared_data:pd.DataFrame, cities: pd.DataFrame) -> None:
    
    save_path = ""
    if os.path.basename(os.getcwd()) != "dataworker": save_path = "."
    
    cities.to_csv(os.path.join(save_path,"cities.csv"))
    cleared_data.to_csv(os.path.join(save_path,"cleared_data.csv"))


if __name__ == "__main__":
    try: 
        path_to_csv = sys.argv[1]
    except IndexError: 
        raise Exception("Path to flights data has to be provided.")
    
    clean_flights_data, cities = data_cleaner(path_to_csv)
    save_cleared_data(clean_flights_data, cities)
    
    
    
    




